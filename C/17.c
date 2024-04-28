#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

int main () {

int pid;


pid = fork();

if(pid > 0){
    int status;
    int fpid;

    fpid = getpid();
    printf("the parentprocess speaking, my pid = %d, i created  a child. its  pid = %d. im going to wait until the child exits\n", fpid, pid);

    pid = wait(&status);
    printf("the parentprocess speaking, my pid = %d,  child %d is just exited, its exit code = %d\n", fpid, pid, status);

} else if(pid == 0){
      int cpid;
      cpid = getpid();
      printf("i am the child process with pid = %d and im going to exit now. buy buy. \n", cpid);
      exit(0);

} else {
      printf("fork error\n");
}

   return 0;
}


