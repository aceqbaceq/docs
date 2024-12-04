#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



int main() {


int fd;
mode_t mode = O_RDONLY;
char *filename = "/home/noroot/temp/nc/fifo1";
fd = open(filename, mode);

if (fd < 0) {
      perror("Creation error");
      exit (1);
}



    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;


    while (1) {
        int ret = poll(fds, 1, -1);
        if (fds[0].revents & POLLIN) {
            printf("Something on fd!\n");
                 char buffer[256];
                 int len = read(fd, buffer, sizeof(buffer) - 1);
                 if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    printf("READ DATA FROM fd : %s", buffer);
                 }

        }

        if (fds[0].revents & POLLHUP) {
            close (fd);
            fd = open(filename, mode);
        }


    }

exit (0);
}


