#include "apue.h"
#include <fcntl.h>

int main (void)
{
    int fd;
    if ((fd=open("fdopen.txt", O_CREAT | O_RDWR, FILE_MODE)) < 0) {
        err_sys("open error");
    }
    FILE* fp;
    char* type;
    *type = 'w';
    fp = fdopen(fd, type);
    fputs("fxck shit", fp);
    fclose(fp);
    close(fd);
    return 0;
}