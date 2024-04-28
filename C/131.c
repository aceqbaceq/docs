#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>



static void sigdown(int signo) {
  pid_t pid_p = getpid();
  printf("WARNING PID=%d got SIGNAL=%d...the process is shutting down\n", pid_p, signo);
  exit(0);
}




pid_t pid;
int finished=0;

int main(void)
    {

      // set custom SIGINT, SIGTERM handlers
      if (sigaction(SIGINT, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
        return 1;
      if (sigaction(SIGTERM, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
        return 2;



       pid = fork();

        if (pid == -1)
        {
           exit(1);
           } 

        else if (pid == 0)
        {

           time_t starttime = time(NULL);
           time_t seconds = 600; 
           time_t endtime = starttime + seconds;
 
              while (starttime < endtime) {
               printf("child: i am running...\n");
               sleep(10);
               starttime = time(NULL);
               }
           exit(0);
            }

        else if (pid > 0)
        {
          pid_t pid_p = getpid();
          printf("parent: parent PID=%d...\n", pid_p);
          printf("parent: child PID=%d...\n", pid);
             }




    while(!finished)
        {
        printf("parent:i am running...\n");
        sleep(10);
        }
    }




















