#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main ()
{
    char buf[1024];
    fgets(buf, 1024, stdin);
    buf[strlen(buf)-1] = 0;
    printf("Input command: ");
    if ( execlp(buf, buf, (char*)0) == -1 ){
        perror("error exec!");
    }
    printf("true end\n");
    int sum = 0;
    printf ("sum = %d\n", ++sum);
    return 0;
}