#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h> // Include this header for close()


int main() {
    struct timespec start, end;
    int sockfd;

    // Get start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create a socket (e.g., AF_INET, SOCK_STREAM)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Get end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the elapsed time
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    if (start.tv_nsec > end.tv_nsec) {
        --seconds;
        nanoseconds += 1000000000;
    }

    printf("Time taken to create socket: %ld seconds %ld nanoseconds\n", seconds, nanoseconds);

    // Close the socket
    close(sockfd);

    return 0;
}


