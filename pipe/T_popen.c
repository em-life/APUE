#include <stdio.h>  
int main()  
{  
    FILE *fp;  
    char buf[20] = {0};  
    fp = popen("ls","r");  
    if(NULL == fp)  
    {  
        perror("popen error!\n");  
        return -1;  
    }  
    while(fgets(buf, 20, fp) != NULL)  
    {  
        printf("%s", buf);  
    }  
    pclose(fp);  
    return 0;  
}  

