#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define SERVER_ADDR "127.0.0.1"

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char message[256];
    int i;

    // Создаем UDP сокет
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    // Отправляем несколько сообщений
    for (i = 0; i < 10; i++) {
        snprintf(message, sizeof(message), "Message %d", i);
        if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("sendto");
            close(sock);
            exit(EXIT_FAILURE);
        }
        printf("Sent: %s\n", message);
        sleep(1);  // Пауза 1 секунда
    }

    close(sock);
    return 0;
}

