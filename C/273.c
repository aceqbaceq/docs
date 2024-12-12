#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }




int rcvbuf_size = 0;
socklen_t len1 = sizeof(rcvbuf_size);
if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, &len1) == -1) {
    perror("getsockopt failed");
} else {
    printf("Socket RECEIVE BUFFER SIZE: %i\n", rcvbuf_size);
}




int sock_error = 0;
socklen_t len = sizeof(sock_error);
if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &sock_error, &len) == -1) {
    perror("getsockopt failed");
} else {
    printf("Socket error: %s\n", strerror(sock_error));
}


    sleep(120);
    close(sockfd);
    return 0;
}




