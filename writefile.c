#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define SIZE 100000

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main (void)
{   
    int cnt = 1;
    int fd;
    if ((fd=open("file100000.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE)) == -1) {
        perror("open error!!!");
        exit(-1);
    }
    for(int i=0; i<SIZE; ++i) {
        char ch[1];
        ch[0] = 'a' + (i%26);
        if (write(fd, ch, 1) != 1) {
            perror("write error!!");
            exit(-1);
        }
    }
    return 0;
}