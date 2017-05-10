#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void pr_stdio(const char *name, FILE *fp) {
    printf("stream = %s, ", name);
    if (fp->_flag & _IONBF)     printf("unbuffered");
    else if (fp->_flag & _IOLBF)    printf("line buffer");
    else printf(", buffer size = %d\n", fp->_bufsiz);
}

int main (void)
{
    FILE* fp;
    fputs("enter any charactre\n",  stdout);
    if (getchar() == EOF) {
        perror("getchar error");
    }
    fputs("one line to standard error\n", stderr);
    
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);
    
    if ((fp = fopen("/etc/motd", "r")) == NULL)
        perror("fopen error");
    if (getc(fp) == EOF)
        perror("getc error");
    pr_stdio("/etc/motd", fp);
    exit(0);
}
