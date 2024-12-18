#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void print_local_and_remote_ip(int sockfd) {
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len;

    // Получаем локальный адрес сокета
    len = sizeof(local_addr);
    if (getsockname(sockfd, (struct sockaddr *)&local_addr, &len) == -1) {
        perror("getsockname failed");
        return;
    }

    // Получаем удалённый адрес сокета
    len = sizeof(remote_addr);
    if (getpeername(sockfd, (struct sockaddr *)&remote_addr, &len) == -1) {
        perror("getpeername failed");
        return;
    }

    // Печатаем локальный и удалённый IP
    printf("Local IP: %s\n", inet_ntoa(local_addr.sin_addr));
    printf("Remote IP: %s\n", inet_ntoa(remote_addr.sin_addr));
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Создаем сокет (например, TCP)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Устанавливаем параметры сокета
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);  // Пример, например порт HTTP
    server_addr.sin_addr.s_addr = inet_addr("8.8.8.8");  // Пример удалённого адреса

    // Подключаемся к серверу
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Печатаем локальный и удалённый IP
    print_local_and_remote_ip(sockfd);

    // Закрываем сокет
    close(sockfd);
    return 0;
}

