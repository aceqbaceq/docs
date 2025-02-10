#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    // Путь к UNIX-сокету
    const char *socket_path = "/run/systemd/journal/dev-log";
    
    // Создаем сокет типа SOCK_DGRAM
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    // Настроим адрес сокета
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    // Отправляем сообщение в сокет
    const char *message = "123";
    ssize_t sent_len = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (sent_len == -1) {
        perror("sendto");
        close(sockfd);
        return 1;
    }

    printf("Сообщение отправлено: %s\n", message);

    // Закрываем сокет
    close(sockfd);

    return 0;
}


