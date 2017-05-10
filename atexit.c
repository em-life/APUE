#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static void ex1() {
    printf("first exit\n");
}

static void ex2() {
    printf("second exit\n");
}

int main ()
{
    if (atexit(ex2) != 0) {
        perror("ex2 error");
    }
    if (atexit(ex1) != 0) {
        perror("ex1 error");
    }
    if (atexit(ex1) != 0) {
        perror("ex1 error");
    }
    // exit(0);
    // printf("wocao");
    return 0;
    printf("wocao");
}