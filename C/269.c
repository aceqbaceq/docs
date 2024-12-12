#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

int main(int argc, char *argv[]) {

    if(argc != 3)
    {
    printf("\n Usage: %s <ip of server>  <port> \n",argv[0]);
    return 1;
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }



    int sockfd;
    int recv_buf_size, send_buf_size;
    socklen_t optlen = sizeof(int);

    // Создаем TCP сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    // Адрес и порт сервера (используем localhost для примера)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( atoi(argv[2]) );
    server_addr.sin_addr.s_addr = inet_addr( argv[1] );

    // Подключаемся к серверу
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    // Получаем текущие размеры буферов для приема и отправки
    if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recv_buf_size, &optlen) < 0) {
        perror("getsockopt SO_RCVBUF");
        close(sockfd);
        return 1;
    }

    if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &send_buf_size, &optlen) < 0) {
        perror("getsockopt SO_RCVBUF");
        close(sockfd);
        return 1;
    }

    // Выводим размеры буферов
    printf("Размер буфера для приема: %d байт\n", recv_buf_size);
    printf("Размер буфера для отправки: %d байт\n", send_buf_size);

    // Закрываем сокет
    close(sockfd);
    return 0;
}

