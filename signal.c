#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 1024

static void sig_int(int);

void sig_int(int signo) {
    printf("Interrupt\n %%");
}

int main (void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        perror("signal error");
    }
    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        buf[strlen(buf)-1] = 0;
        if ( (pid = fork()) < 0)
            perror("fork error");
        if (pid == 0) {
            execlp(buf, buf, (char*)0);
            printf("couldn't execute: %s", buf);
            printf("I am finish!!!");
            exit(127);
        }
        
        if ((pid = waitpid(pid, &status, 0)) < 0)
            perror("waitpid error");
        printf("%% ");
    }
    return 0;
}