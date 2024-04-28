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

    pid = fork();

    if (pid == -1)
        {
        exit(1);
        } 
    else if (pid == 0)
        {
           time_t starttime = time(NULL);
           time_t seconds = 3; 
           time_t endtime = starttime + seconds;
 
           while (starttime < endtime) {
            sleep(1);
            printf("child: i am running...\n");
            starttime = time(NULL);
            }

          exit(0);
        }

    while(!finished)
        {
        printf("parent:i am running...\n");
        sleep(1);
        }
    }
