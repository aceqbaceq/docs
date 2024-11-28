#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <unistd.h>

int main() {
    struct pollfd fds[1];
    fds[0].fd = STDERR_FILENO;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    while (1) {
        int ret = poll(fds, 1, -1);
        if (ret == -1) {
            perror("poll");
            return 1;
        }
        if (fds[0].revents & POLLIN) {
            printf("Something on STDERR!\n");
        }
                sleep(10);

    }
}


