#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define SERVER_ADDR "127.0.0.1"

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[256];

    // Создаем UDP сокет
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Привязываем сокет к адресу и порту
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Listening on %s:%d...\n", SERVER_ADDR, SERVER_PORT);

    // Программа просто ждет, не читая данные
    while (1) {
        // Принимаем данные, но не делаем с ними ничего
        //recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
    sleep(20);
    }

    close(sock);
    return 0;
}

