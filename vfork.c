#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int glob = 6;
char buf[] = "a write to stdout\n";
int main (void) 
{
    pid_t pid;
    int var = 88;

    int fd;
    fd = open("fork_file.txt", O_WRONLY|O_CREAT|O_TRUNC, FILE_MODE);

    if (write(fd, buf, sizeof(buf)-1) != sizeof(buf)-1)
        perror("write error");
    printf("before fork\n");

    strcpy(buf,"--------------\n");

    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
        perror("write file error!!");
    }

    char str[20] = "fuck you!!!";
    if ((pid=vfork()) < 0)
        perror("vfork error");
    else if (pid == 0) {
        glob++;
        var++;
        // if (write(fd, str, sizeof(str)-1) != sizeof(str)-1) {
        //     perror("write file error!!");
        // }
    } else {
        sleep(2);
        // char s[] = "shit!!";
        // if (write(fd, s, sizeof(s)-1) != sizeof(s)-1) {
        //    perror("write file error!!");
        // }
        _exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    close(fd);
    exit(0);
}