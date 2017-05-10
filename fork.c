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
    off_t off_set = lseek(fd, 0, SEEK_CUR);
    printf("start at : %ld\n", off_set);

    if (write(fd, buf, sizeof(buf)-1) != sizeof(buf)-1)
        perror("write error");
    printf("before fork\n");

    off_set = lseek(fd, 0, SEEK_CUR);
    printf("write once at : %ld\n", off_set);

    strcpy(buf,"--------------\n");

    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
        perror("write file error!!");
    }

    off_set = lseek(fd, 0, SEEK_CUR);
    printf("write twice at : %ld\n", off_set);

    char str[20] = "fuck you!!!";
    if ((pid=fork()) < 0)
        perror("fork error");
    else if (pid == 0) {
        glob++;
        var++;
        off_set = lseek(fd, 0, SEEK_CUR);
        printf("child start write at : %ld\n", off_set);
        if (write(fd, str, sizeof(str)-1) != sizeof(str)-1) {
            perror("write file error!!");
        }
        off_set = lseek(fd, 0, SEEK_CUR);
        printf("child end write at : %ld\n", off_set);
    } else {
        sleep(2);
        char s[] = "shit!!";
        off_set = lseek(fd, 0, SEEK_CUR);
        printf("parent start write at : %ld\n", off_set);
        if (write(fd, s, sizeof(s)-1) != sizeof(s)-1) {
           perror("write file error!!");
        }
        off_set = lseek(fd, 0, SEEK_CUR);
        printf("parent start write at : %ld\n", off_set);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    close(fd);
    exit(0);
}