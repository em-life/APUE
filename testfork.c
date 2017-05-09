#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (void)
{
    pid_t fpid;
    if ((fpid = fork()) < 0) {
        perror("fork fail");
    }
    if (fpid == 0) {
        printf("child pid = %d\n", fpid);
    } else {
        printf("parent pid = %d\n", fpid);
    }
    return 0;
}