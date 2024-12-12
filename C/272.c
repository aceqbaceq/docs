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

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(45);  // Порт, на котором нет сервиса
    server_addr.sin_addr.s_addr = inet_addr("172.16.10.11");

    // Пытаемся подключиться
    int result = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (result == -1) {
        // Ошибка подключения, проверяем errno
        perror("Connect failed");


int sock_error = 0;
socklen_t len = sizeof(sock_error);
if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &sock_error, &len) == -1) {
    perror("getsockopt failed");
} else {
    printf("Socket error: %s\n", strerror(sock_error));
}



        // Печатаем ошибку из errno
        switch (errno) {
            case ECONNREFUSED:
                printf("Connection refused (ECONNREFUSED)\n");
                break;
            case ETIMEDOUT:
                printf("Connection timed out (ETIMEDOUT)\n");
                break;
            case EHOSTUNREACH:
                printf("Host unreachable (EHOSTUNREACH)\n");
                break;
            default:
                printf("Other error: %s\n", strerror(errno));
        }
    } else {
        printf("Connected successfully\n");
    }

    sleep(120);
    close(sockfd);
    return 0;
}



