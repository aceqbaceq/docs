#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[], char *envp[])
{

char const path[] = "/bin/bash";
char const * ptr_path = path;

char arg1[] = "-bash";
char * const ptr_arg[] = { arg1, NULL };


char env1[22] = "VAR1=12";
char env2[22] = "VAR2=folder";
char * const ptr_env[] = { env1, env2, NULL };


      pid_t pid = -1;
      pid = fork();

        if (pid == -1)
        {
           printf("ERROR: fork() is failed\n");
           exit(1);
           } 

        else if (pid == 0)
        {
              int ret_c = -1;
              ret_c =  execve(ptr_path, ptr_arg,  ptr_env);

                if (ret_c == -1)
                {
                    printf ("ERROR: execve() is FAILED\n" );
                    exit(1);
                    } 


           exit(0);
            }


        else if (pid > 0)
        {
          pid_t pid_p = getpid();
          printf("parent: parent PID=%d...\n", pid_p);
          printf("parent: child PID=%d...\n", pid);

          int wstatus = -1;
          int ret_c = -1;
          ret_c = wait(&wstatus);

          if ( ret_c == -1 )
          {

               if ( WIFEXITED(wstatus) )
               {
                 int exit_status = WEXITSTATUS(wstatus);        
                 printf("Exit status of the child was %d\n",  exit_status);
                                     }

           exit(2);
                  }

          else 
            printf ("notice: the child process has exited successfully.\n");
       


          exit(0);
                }


exit (0);



}


