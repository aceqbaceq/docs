
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


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


    char ch3[4];
    memset(ch3, '0', sizeof(ch3));


    for (int t=0; t<2; t++)
    {
    if (write(pipefd[1], ch3, sizeof(ch3)) < 0)
    {
	perror("write()");
	printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
    }
    printf ("t = %i\n", t);
    }




    char ptr_buf[100];
    memset(ptr_buf, 0x00, sizeof(ptr_buf));



    if (read(pipefd[0], ptr_buf, 100) == -1)
    {
	perror("read()");
	printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
    }


    char const * ptr_buf2 = ptr_buf;
    fputs(ptr_buf2, stdout);
    fputc(0x0a,stdout);


    sigaction(SIGPIPE, &oldact, NULL);



    return 0;
}






