#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "apue.h"
#include <fcntl.h>
#include <errno.h>


int main ()
{
    int fd;
    int buf;
    if ((fd=open("tt.lock", O_CREAT|O_WRONLY, FILE_MODE)) < 0) {
        err_sys("open error");
    }
    int num = 'a';
    for(int i=0; i<1000; ++i) {
        write(fd, &num, 1);
    }
    return 0;
}
