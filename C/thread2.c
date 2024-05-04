#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/syscall.h>



void signal_handler(int signum, siginfo_t *info, void *extra)
{
    printf("Handler thread ID: %ld\n", syscall(SYS_gettid));
}




void set_signal_handler(void)
{
    struct sigaction action;

    action.sa_flags = SA_SIGINFO;     
    action.sa_sigaction = signal_handler;
    sigaction(SIGINT, &action, NULL);
}




void *task(void* argv)
{
    printf("Thread ID: %ld, pid=%i\n", syscall(SYS_gettid), getpid());
    for(;;) {
        sleep(1);
    }
}




void main(void)
{
    pthread_t t1, t2, t3;
    
    set_signal_handler();
    printf("Thread ID (main thread): %ld\n", syscall(SYS_gettid));

    pthread_create(&t1, NULL, task, NULL);
    pthread_create(&t2, NULL, task, NULL);
    pthread_create(&t3, NULL, task, NULL);

   for(;;) {
       sleep(1);
   } 
}


