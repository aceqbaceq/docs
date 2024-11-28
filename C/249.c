#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open




int main() {
    fd_set readfds;
    int ret;

     int fd1 = open("/tmp/1.txt", O_RDONLY);
        if (ret == -1) {
            perror("open error");
            exit(1);
        }


     int fd2 = open("/tmp/1.txt", O_RDONLY);
        if (ret == -1) {
            perror("open error");
            exit(1);
        }

    
    
     int fd3 = open("/tmp/1.txt", O_RDONLY);
        if (ret == -1) {
            perror("open error");
            exit(1);
        }

     int temp1  = (fd1 > fd2) ? fd1 : fd2;
     int max_fd = (fd3 > temp1) ? fd3 : temp1;



         FD_ZERO(&readfds);
         FD_SET(fd1,&readfds);
         FD_SET(fd2,&readfds);
         FD_SET(fd3,&readfds);


         ret = select(max_fd +1, &readfds, NULL, NULL, NULL);
        
        if (ret == -1) {
            perror("select error");
            exit(1);
        }



        if (FD_ISSET(fd1, &readfds)) {
                printf("fd1 descriptor is returned\n");
        }


        if (FD_ISSET(fd2, &readfds)) {
                printf("fd2 descriptor is returned\n");
        }

        if (FD_ISSET(fd3, &readfds)) {
                printf("fd3 descriptor is returned\n");
        }




    return 0;
}


