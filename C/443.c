#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 2323
#define IP_ADDRESS "127.0.0.12"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Создаем сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Настраиваем опции сокета (опционально)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Заполняем структуру адреса
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // Преобразуем IP-адрес из строки в сетевой порядок байт
    if (inet_pton(AF_INET, IP_ADDRESS, &address.sin_addr) <= 0) {
        perror("Invalid address");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Привязываем сокет к IP и порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Начинаем слушать входящие подключения
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on %s:%d\n", IP_ADDRESS, PORT);

    while (1) {
        // Принимаем новое подключение
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted\n");

        // Можно здесь читать/писать данные с new_socket

        close(new_socket);
    }

    close(server_fd);
    return 0;
}


