#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    int max_fd,ret;


    while (1) {

         FD_ZERO(&readfds);
         FD_SET(STDIN_FILENO,&readfds);

         ret = select(1, &readfds, NULL, NULL, NULL);
        
        if (ret == -1) {
            perror("select error");
            exit(1);
        }


        // Check if stdin (fd=0) is ready to read
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char buffer[256];
            int len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	    if (len > 0) {
                buffer[len] = '\0';  // Null-terminate the string
                printf("READ DATA FROM STDIN : %s", buffer);
            }
        }




    }



    return 0;
}


