#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>








int main()
{

  pid_t pid_p = getpid();
  printf("parent PID = %d\n", pid_p);


  int md = -1;
  md = open("/dev/ptmx", O_RDWR | O_NOCTTY);
  dprintf (STDOUT_FILENO, "md=%i\n", md);

  int sl1 = -1;
  sl1 = grantpt(md);
  sl1 = unlockpt(md);


  char * ptr_sln = NULL;
  ptr_sln = ptsname(md);
  printf ("pts name = %s\n", ptr_sln);




      pid_t pid = -1;
      pid = fork();

        if (pid == -1)
        {
           close(md);                     /* Don't leak file descriptors */
           printf("ERROR: fork() is failed\n");
           exit(1);
           } 





        else if (pid == 0)
        {

                 if (setsid() == -1)                 /* Start a new session */
                   printf("ERROR: setsid() is failed\n");

                 close(md);                         /* Not needed in child */

                 int slaveFd = open(ptr_sln, O_RDWR);     /* Becomes controlling tty */
                 if (slaveFd == -1)
                     printf("ERROR: open pts/N is failed\n");



                  /* Duplicate pty slave to be child's stdin, stdout, and stderr */
                  dup2(slaveFd, STDIN_FILENO);
                  dup2(slaveFd, STDOUT_FILENO);
                  dup2(slaveFd, STDERR_FILENO);

                  if (slaveFd > STDERR_FILENO)        /* Safety check */
                     close(slaveFd);                 /* No longer need this fd */

                 char buffer[256];
                 int len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
                 if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    printf("READ DATA FROM STDIN : %s", buffer);
                 }


                  sleep(180);
                  return(0);
            }



        else if (pid > 0)
        {
          printf("child PID = %d\n", pid);

          dprintf (md, "12345\n");
                 char buffer[256];
                 int len = read(md, buffer, sizeof(buffer) - 1);
                 if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    printf("PARENT PROCESS. READ DATA FROM /dev/ptmx : %s", buffer);
                 }

          sleep (60);
          close (md);

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













