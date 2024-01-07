#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = vfork();

    if (pid == 0) {
    sleep(2);
    _exit(0);
    }

      //printf("parent: I am exiting\n");

     return(0);
}


