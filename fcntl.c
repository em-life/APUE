#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[])
{
    int accmode, val;
    if (argc != 2) {
        perror("args is not right!");
        exit(-1);
    }
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl error for fd = %d\n", atoi(argv[1]));
        exit(-1);
    }
    accmode = val & O_ACCMODE;
    if (accmode == O_RDONLY)    printf("read only");
    else if (accmode == O_WRONLY)   printf("write only");
    else if (accmode == O_RDWR)     printf("read write");
    else { perror("unknow access mode"); exit(-1); }

    if (val & O_APPEND)     printf(", append");
    if (val & O_NONBLOCK)   printf(", nonblocking");
    #if !defined(_POSIX_SOURCE) && defined(O_SYNC)
        if (val & O_SYNC)   printf(", sys\nchronous writes");
#endif
    putchar('\n');
    exit(0);
    
}