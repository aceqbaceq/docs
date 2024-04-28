#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>





int main(void)
    {

       int finished=0;
       pid_t pid = getpid();
       printf("process PID=%d \n", pid);
       

    while(!finished)
        {
        printf("i am running...\n");
        sleep(1);
        }
    }




















