#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    char ch;
    while((ch = fgetc(stdin)) != -1) {
        if (putc(ch, stdout) == EOF) {
            perror("putc error!");
        }
    }
    if (ferror(stdin)) {
        perror("input error!");
    }
    return 0;
}