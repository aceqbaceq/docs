#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {

   pid_t chpid;
   int status;

   int variable = 9;

   chpid = fork();

   if (chpid > 0) {
      waitpid(-1, &status, WNOHANG);
   }
   else {
      variable = 42;
      printf("The child: variable= %d\n", variable);
      sleep (300);
      return(0);
   }
   printf("The parent: variable= %d. The parent is exit.\n", variable);


   return(0);
}


