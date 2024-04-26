
/* pidns_init_sleep.c

   Copyright 2013, Michael Kerrisk
   Licensed under GNU General Public License v2 or later

   A simple demonstration of PID namespaces.
*/
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process */



    pid_t child_pid;
    int finished = 0;



void zombie_hunter(int sig)
    {
    int status;
    wait(&status);
    printf ("got  SIGCHLD \n");
    printf("parent: Got status %d from child\n",status);

    }



void kill_child(int sig)
    {

     printf("parent: SIGINT is catched \n" );
      int sigk = 9;
      kill(child_pid, sigk);
     finished = 1;

    }


void sigt (int sig)
    {
    pid_t p2 = getpid();
    printf ("pid=l%d, got  SIGTERM ... shutdown\n", p2);
    exit(0);

    }




#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)


static int              /* Start function for cloned child */
childFunc(void *arg)
{


    printf("child  PID  = %ld\n", (long) getpid());
    printf("child PPID = %ld\n", (long) getppid());


    int mnt1;


    mnt1 = mount("none", "/", NULL, MS_REC|MS_PRIVATE, NULL);
    if (mnt1 == -1)
    errExit("mount");



    mnt1 = mount("none", "/proc", NULL, MS_REC|MS_PRIVATE, NULL);
    if (mnt1 == -1)
    errExit("mount");



    mnt1 = umount("/proc");
    if (mnt1 == -1)
    errExit("umount");


    mnt1 =  mount("proc", "/proc", "proc", MS_NOSUID|MS_NODEV|MS_NOEXEC, NULL);
    if (mnt1 == -1)
    errExit("mount");






   char* argv[] = { "sleep", "1200", NULL };
   char* envp[] = { NULL };
   if (execve("/bin/sleep", argv, envp) == -1)
    perror("Could not execve");
   return 1;

   exit(EXIT_SUCCESS);
}


#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];    /* Space for child's stack */





int
main(int argc, char *argv[])
{

    signal(SIGCHLD,zombie_hunter);
    signal(SIGINT, kill_child);
    signal(SIGTERM,sigt);

    printf("parent  PID  = %ld\n", (long) getpid());



    child_pid = clone(childFunc,
                    child_stack + STACK_SIZE,   /* Points to start of
                                                   downwardly growing stack */
                    CLONE_NEWPID|CLONE_NEWNS|SIGCHLD, argv[1]);

    if (child_pid == -1)
        errExit("clone");

    printf("PID returned by clone(): %ld\n", (long) child_pid);

//    if (waitpid(child_pid, NULL, 0) == -1)      /* Wait for child */
//        errExit("waitpid");

  while(!finished)
        {
        //printf("parent:i am running...\n");
        sleep(20);
        }



    exit(EXIT_SUCCESS);
}



