#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

 void vasya(int sig){
      printf("  i am inside the handler SIGINT(-2+) \n");
       sleep (30);
      printf("  i exit from the handler SIGINT(-2-) \n");

       };


 void petya(int sig){
      printf("i am inside the handler SIGHUP(-1+) \n");
       sleep (30);
      printf("i exit from the handler SIGHUP(-1-) \n");

       };


 void kolya(int sig){
      printf("   i am inside the handler SIGUSR1(-10+) \n");
       sleep (30);
      printf("   i exit from the handler SIGUSR1(-10-) \n");

       };






int main(void)
{
//Register signal handler through the signal() function
signal(SIGINT,  vasya);
signal(SIGHUP,  petya);
signal(SIGUSR1, kolya);

printf("parent: parentpid=%d\n", getpid());

pid_t pid_c;



while(1)
{
//simulate a delay -- as if the program is doing some other stuff
sleep(10);
}

return 0;
}

