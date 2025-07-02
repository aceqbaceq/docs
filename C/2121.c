#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>

pid_t pid;
int finished=0;

void zombie_hunter(int sig)
    {
    int status;
    waitpid(pid, &status, 0);
    printf("parent: Got status %d from child\n",status);
    finished=1;
    }

int main(void)
    {
    signal(SIGCHLD,zombie_hunter);

    while(!finished)
        {
       pause();

        }
    }
