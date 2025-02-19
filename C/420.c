#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netfilter/nfnetlink_log.h>
#include <unistd.h>

#define NL_BUF_SIZE 4096

int main() {
    int sock_fd;
    struct sockaddr_nl sa;
    char buffer[NL_BUF_SIZE];
    
    // Создаем Netlink сокет
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_NETFILTER);
    if (sock_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Привязываем сокет к группе NFLG (группа 1)
    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;
    sa.nl_pid = getpid();
    sa.nl_groups = 1; // Подписка на группу 1

    if (bind(sock_fd, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
        perror("bind");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Подписан на NFLOG группу 1. Ожидание событий...\n");
    
    // Читаем события из Netlink сокета
    while (1) {
        ssize_t len = recv(sock_fd, buffer, sizeof(buffer), 0);
        if (len < 0) {
            perror("recv");
            break;
        }
        printf("Получено сообщение от NFLOG (длина: %zd байт)\n", len);
    }

    close(sock_fd);
    return 0;
}


