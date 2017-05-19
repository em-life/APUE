
#include <signal.h>
#include "apue.h"
static void sig_quit(int);
static void print_mask(sigset_t mask);

int
main(void)
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        printf("can't catch SIGQUIT");
        exit(1);
    }

    /*
     * Block SIGQUIT and save current signal mask.
     */
    sigemptyset(&newmask);              //empty newmask (newmask is  signal set)
    printf("empty: ");
    print_mask(newmask);
    sigaddset(&newmask, SIGQUIT);       
    printf("add SIGQUIT: ");
    print_mask(newmask);

    //block the signal use newmask, and the result is in newmask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error\n");
        exit(1);
    }

    printf("SIGBLOCK SIGQUIT: ");
    printf(" new mask = ");
    print_mask(newmask);
    printf("oldmask = ");
    print_mask(oldmask);


    sleep(5); /* SIGQUIT here will remain pending */

    if (sigpending(&pendmask) < 0) {
        printf("sigpending error\n");
        exit(1);
    }
    if (sigismember(&pendmask, SIGQUIT))
        printf("\nSIGQUIT pending\n");
    printf("pending mask = ");
    print_mask(pendmask);
    /*
     * Reset signal mask which unblocks SIGQUIT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error\n");
        exit(1);
    }
    printf("SIGQUIT unblocked\n");

    sleep(5); /* SIGQUIT here will terminate with core file */
    exit(0);
}

static void
sig_quit(int signo)
{
    printf("caught SIGQUIT!!!\n");
    // printf("quit!!!\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        printf("can't reset SIGQUIT\n");
        exit(1);
    }
}


static void 
print_mask(sigset_t mask)
{
    printf("mask: ");
    char ch[64];
    for(int i=0; i<64; ++i) {
        if (sigismember(&mask, i+1)) {
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