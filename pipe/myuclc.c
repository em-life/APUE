#include <stdio.h>
#include <ctype.h>
#include "apue.h"

int main (void)
{
    int c;
    while((c = getchar()) != EOF) {
        if (isupper(c)) {
            c = tolower(c);
        }
        if (putchar(c) == EOF) {
            err_sys("ouput error");
        }
        if (c == '\n') {
            fflush(stdout);
        }
    }
    return 0;
}