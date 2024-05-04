#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/syscall.h>



void *threadfn1(void *p)
{
    printf("Thread ID: %ld, pid=%i\n", syscall(SYS_gettid), getpid());
    while(1){
	//printf("thread1\n");
	sleep(2);
    }
    return 0;
}

void *threadfn2(void *p)
{
     printf("Thread ID: %ld, pid=%i\n", syscall(SYS_gettid), getpid());
    while(1){
	//printf("thread2\n");
	sleep(2);
    }
    return 0;
}

void *threadfn3(void *p)
{
    printf("Thread ID: %ld, pid=%i\n", syscall(SYS_gettid), getpid());
    while(1){
	//printf("thread3\n");
	sleep(2);
    }
    return 0;
}


void handler(int signo, siginfo_t *info, void *extra) 
{
        // int i;
	//puts("signal");
	//sleep(2);
       printf("\n============\nThread ID: %ld, pid=%i\n===============\n", syscall(SYS_gettid), getpid());
       pthread_exit(0);
}

void set_sig_handler(void)
{
        struct sigaction action;


        action.sa_flags = SA_SIGINFO; 
        action.sa_sigaction = handler;

        if (sigaction(SIGTERM, &action, NULL) == -1) { 
            perror("sigusr: sigaction");
            _exit(1);
        }

}

int main()
{
    printf("Thread ID (main thread): %ld, pid=%i\n", syscall(SYS_gettid), getpid());
    pthread_t t1,t2,t3;
    set_sig_handler();

    pthread_create(&t1,NULL,threadfn1,NULL);
    pthread_create(&t2,NULL,threadfn2,NULL);
    pthread_create(&t3,NULL,threadfn3,NULL);
    for(;;)    
      sleep(1);
    //pthread_exit(NULL);
    return 0;
}


