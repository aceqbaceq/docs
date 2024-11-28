#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    int ret;
    


         FD_ZERO(&readfds);
         FD_SET(STDIN_FILENO,&readfds);
         FD_SET(STDOUT_FILENO,&readfds);
         FD_SET(STDERR_FILENO,&readfds);


         ret = select(3, &readfds, NULL, NULL, NULL);
        
        if (ret == -1) {
            perror("select error");
            exit(1);
        }



        if (FD_ISSET(STDIN_FILENO, &readfds)) {
                printf("STDIN descriptor is returned\n");
        }


        if (FD_ISSET(STDOUT_FILENO, &readfds)) {
                printf("STDOUT descriptor is returned\n");
        }

        if (FD_ISSET(STDERR_FILENO, &readfds)) {
                printf("STDERR descriptor is returned\n");
        }




    return 0;
}


