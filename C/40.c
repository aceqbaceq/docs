#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
//Register signal handler through the signal() function
//signal(SIGINT, SIG_IGN);
//signal(SIGTERM, SIG_IGN);

printf("parent: parentpid=%d\n", getpid());

pid_t pid_c;

pid_c = fork();
if (pid_c == 0){
    //child process 
    sleep (1);
    return (0);
     };



pid_c = fork();
if (pid_c == 0){
    //child process 
    sleep (180);
    return (0);
     };

sleep (3);


pid_t ret_c;

printf("parent:i am before waitpid command\n");
ret_c = waitpid(-1,NULL,WNOHANG);
printf("parent:i am behind waitpid command\n");

printf("waitpid return code=%d\n", ret_c );

while(1)
{
//simulate a delay -- as if the program is doing some other stuff
sleep(10);
}

return 0;
}

static void vasya(int sig){
      printf("i am inside the handler\n");
      printf("i am before waitpid\n");
      waitpid(-1,NULL,0);
      printf("i am behind waitpid\n");
       };
