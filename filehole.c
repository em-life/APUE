#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main (void)
{
    char str1[] = "abcde";
    char str2[] = "ABCDE";
    int fd;
    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        perror("create error!\n");
    }
    if (write(fd, str1, 5) != 5) {
        perror("write error!");
        exit(-1);
    }
    if (lseek(fd, 40, SEEK_SET) == -1) {
        perror("write error!");
        exit(-1);
    }
    if (write(fd, str2, 5) != 5) {
        perror("write error!");
        exit(-1);
    }
    return 0;
}