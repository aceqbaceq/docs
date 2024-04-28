#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>



static void sigalarm() {
  pid_t pid_p = getpid();
  printf("WARNING: SIGALRM is caught, PID=%d ...the process is shutting down\n", pid_p);
  exit(0);
}




static void sigdown(int signo) {
  pid_t pid_p = getpid();
  printf("WARNING PID=%d got SIGNAL=%d...the process is shutting down\n", pid_p, signo);
  exit(0);
}





int main(void)
    {

       alarm (10);
       pid_t pid;
       int finished=0;
       pid = getpid();
       printf("process PID=%d \n", pid);
       

      // set custom SIGINT, SIGTERM handlers
      if (sigaction(SIGINT, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
        return 1;
      if (sigaction(SIGTERM, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
        return 2;

      if (sigaction(SIGALRM, &(struct sigaction){.sa_handler = sigalarm}, NULL) < 0)
        return 3;





    while(!finished)
        {
        printf("i am running...\n");
        sleep(1);
        }
    }




















