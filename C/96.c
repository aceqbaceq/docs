


#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


static void handler(int sig) {    struct sigaction act = { 	.sa_handler = SIG_DFL, 	.sa_flags = 0,     };
    sigaction(sig, &act, NULL);
    printf("Got signal %d\n", sig);
    kill(getpid(), sig);
}



int main(int argc, char **argv) {
    int pipefd[2];
    bool ignore = argc > 1 && argv[1][0] != '0';


    struct sigaction oldact, act = { 	.sa_handler = ignore ? SIG_IGN : handler, 	.sa_flags = 0,     };
    sigaction(SIGPIPE, &act, &oldact);



    pipe(pipefd);
    //close(pipefd[0]); // reader
    if (write(pipefd[1], "Hello", 6) < 0){
	perror("write()");
	printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
   }

    sigaction(SIGPIPE, &oldact, NULL);
    return 0;
}





