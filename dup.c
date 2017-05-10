#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main ()
{
    int fd;
    if ((fd=creat("test_dup.txt", FILE_MODE)) < 0) {
        perror("creat error!\n");
        exit(-1);
    }
    char str[100] = "hello world!";
    if (write(fd, str, strlen(str)) != strlen(str)) {
        perror("write error!");
    }
    printf("fd = %d\n", fd);
    int newfd;
    newfd = dup(fd);
    printf("newfd = %d\n", newfd);
    char append[100] = "lihaile";
    if (write(newfd, append, strlen(append)) != strlen(append)) {
        perror("write error!");
    }
    
    return 0;
}