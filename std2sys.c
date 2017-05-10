#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    FILE* fp;
    if ((fp=fopen("file.txt", "w")) == NULL) {
        fprintf(stderr, "file open error!");
    }
    fprintf(fp, "hello file:");
    fprintf(fp, "fp\n");
    int newfd = dup(fileno(fp));
    char str[100] = "append";
    write(newfd, str, strlen(str));
    fclose(fp);
    close(newfd);
    return 0;
}