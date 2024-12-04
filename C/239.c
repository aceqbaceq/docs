#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>


#define TIMEOUT -1  // Timeout in milliseconds (5 seconds)

int main() {
    struct pollfd fds[2];
    int ret;

    // Set up the pollfd structure for stdin (file descriptor 0)
    fds[0].fd = STDIN_FILENO;  // Standard input (stdin)
    fds[0].events = POLLIN;     // We want to monitor for input events (POLLIN)
    fds[0].revents = 0;         // Initialize revents to 0

    // Set up the pollfd structure for a socket (just an example)
    // Here, we're using a dummy file descriptor (e.g., socket) for the second file
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(1);
    }

    fds[1].fd = sockfd;        // Example socket (could be connected to a server)
    fds[1].events = POLLIN;    // Monitor for readable events
    fds[1].revents = 0;        // Initialize revents to 0

    // Now we'll wait for events on these file descriptors
    while (1) {
        ret = poll(fds, 2, TIMEOUT); // Wait for events on 2 file descriptors with 5 sec timeout

        if (ret == -1) {
            perror("poll error");
            exit(1);
        } else if (ret == 0) {
            printf("Timeout reached! No events occurred in the last %d ms\n", TIMEOUT);
        } else {
            if (fds[0].revents & POLLIN) {
                char buffer[256];
                int len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
                if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    printf("You typed: %s", buffer);
                }
            }

            if (fds[1].revents & POLLIN) {
                // Here we would read data from the socket (simulated in this case)
                char buffer[256];
                int len = read(sockfd, buffer, sizeof(buffer) - 1);
                if (len > 0) {
                    buffer[len] = '\0';
                    printf("Data from socket: %s", buffer);
                }
            }
        }
    }

    close(sockfd);  // Close the socket file descriptor
    return 0;
}
