#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/netfilter_ipv4.h>



int get_original_destination(int client_fd, struct sockaddr_in *orig_dst) {
    socklen_t len = sizeof(*orig_dst);
    memset(orig_dst, 0, len);
    orig_dst->sin_family = AF_INET;

    if (getsockopt(client_fd, SOL_IP, SO_ORIGINAL_DST, orig_dst, &len) < 0) {
        perror("getsockopt(SO_ORIGINAL_DST) failed");
        return -1;
    }

    return 0;
}




int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 1. Создаем TCP сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // 2. Привязываем к 0.0.0.0:12345
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Слушаем
    if (listen(server_fd, 10) < 0) {
        perror("listen() failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port 12345...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept() failed");
            continue;
        }

        printf("Connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        struct sockaddr_in orig_dst;
        if (get_original_destination(client_fd, &orig_dst) == 0) {
            printf("Original destination IP: %s\n", inet_ntoa(orig_dst.sin_addr));
            printf("Original destination port: %d\n", ntohs(orig_dst.sin_port));
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}


