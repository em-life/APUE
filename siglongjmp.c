#include <setjmp.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include "apue.h"
static void	sig_usr1(int), sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

void print_mask(sigset_t sigset) {
	char ch[64];
	for(int i=0; i<64; ++i) {
		if (sigismember(&sigset, i+1)) {
			ch[i] = 1;
		} else {
			ch[i] = 0;
		}
	}
	for(int i=63; i>=0; --i) {
		printf("%d", ch[i]);
	}
	printf("\n");
}

void pr_mask(const char *str)
{
	sigset_t sigset;
//	sigset = jmpbuf.__mask_was_saved;
	int errno_save;
	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0)
		err_sys("sigprocmask error");
	printf("%s", str);
	printf("sigset : ");
	print_mask(sigset);
	if (sigismember(&sigset, SIGINT))	
		printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT))	
		printf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1))	
		printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM))	
		printf("SIGALRM ");
	printf("\n");
	errno = errno_save;
}

int main (void)
{
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	if (sigsetjmp(jmpbuf, 1)) {
	// if (setjmp(jmpbuf)) {
		pr_mask("ending main: ");
		exit(0);
	}
	// printf("what the fuck\n");
	canjump = 1;
	for(;;)
		pause();
}

static void sig_usr1(int signo)
{
	time_t starttime;
	if (canjump == 0) 
		return;
	pr_mask("start sig_usr1: ");
	alarm(3);
	starttime = time(NULL);
	for(;;)
		if (time(NULL) > starttime + 5)
			break;
	pr_mask("finishing sig_usr1: ");
	canjump = 0;
	siglongjmp(jmpbuf, 1);
	// longjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
	pr_mask("in sig_alrm: ");
	return;
}