#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static void sig_usr(int signo) {
    if (signo == SIGUSR1) 
        printf("receive SIGUSR1\n");
    else if (signo == SIGUSR2) 
        printf("receive SIGUSR2\n");
    else {
        fprintf(stderr, "receive signal %d\n", signo);
        exit(-1);
    }
    return;
}

int main (void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("can't catch SIGUSR1");
        exit(-1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("can't catch SIGUSR2");
        exit(-1);
    }
    int i=0;
    for(;;) {
        pause();
        printf("i = %d\n", i++);
    }
}