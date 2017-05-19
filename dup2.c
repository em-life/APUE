#include "apue.h"
#include <fcntl.h>

int main (void)
{
    int fd;
    if ((fd=open("dup2.txt", O_CREAT|O_WRONLY, FILE_MODE)) < 0) {
        err_sys("open file error");
    }
    int fd1;
    dup2(fd, fd1);
    close(fd);
    write(fd1, "fxck shit", 9); 
    return 0;   
}