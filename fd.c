#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main (void)
{
    int fd1, fd2;
    if ((fd1=open("fd_file.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE)) == -1) {
        perror("open file error");
        exit(-1);
    }
    if ((fd2=open("fd_file.txt", O_WRONLY, FILE_MODE)) == -1) {
        perror("open file error");
        exit(-1);
    }
    char str1[] = "fuck!.!";
    char str2[] = "shit!";

    if(write(fd1, str1, strlen(str1)) < 0) {
        perror("write str1 error!!!\n");
    }
    if(write(fd2, str2, strlen(str2)) < 0) {
        perror("write str2 error!!!\n");
    }
    close(fd1);
    close(fd2);
    return 0;
}