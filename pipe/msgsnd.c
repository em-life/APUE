#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/msg.h> 

#define MAX_TEXT 512
// int msgsnd(int msgid, const void *ptr, size_t nbytes, int flag);
struct msg_st{
    long int msg_type;
    char buf[MAX_TEXT];
};

int main (void)
{
    int running = 1;
    struct msg_st data;
    int msgid = -1;
    data.msg_type = 1;
    msgid = msgget((key_t)2333, 0666 | IPC_CREAT);
    printf("msgid = %d", msgid);
    if (msgid == -1) {
        fprintf(stderr, "msgget error!");
        exit(EXIT_FAILURE);
    }
    char buffer[MAX_TEXT];
    while(running) {
        printf("enter some word: ");
        fgets(buffer, MAX_TEXT, stdin);
        strcpy(data.buf, buffer);
        if ( msgsnd(msgid, &data, MAX_TEXT, IPC_NOWAIT) == -1) {
            fprintf(stderr, "msgsnd failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE); 
        }
        if(strncmp(data.buf, "end", 3) == 0) {
            running = 0;
        }
        sleep(1);
    }
    return 0;
}