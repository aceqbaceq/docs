#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int err;

    // Создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Настроим адрес сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(45);  // Порт, к которому мы пытаемся подключиться
    server_addr.sin_addr.s_addr = inet_addr("172.16.10.11");  // Адрес удаленного хоста

    // Пытаемся подключиться
    int connect_status = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if (connect_status < 0) {
        // Если соединение не удается, проверяем ошибку
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, (socklen_t *)&err) < 0) {
            perror("getsockopt failed");
            close(sockfd);
            exit(1);
        }

        // Проверим, какая ошибка произошла
        if (err == ECONNREFUSED) {
            printf("Connection refused (RST received).\n");
        } else {
            printf("Other error: %s\n", strerror(err));
        }
    } else {
        printf("Connected successfully!\n");
    }


    sleep(60);
    
    // Закрываем сокет
    close(sockfd);
    return 0;
}

