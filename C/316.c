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
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }


    // Адрес и порт сервера 
    struct sockaddr_in6 server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons( atoi(argv[2]) );
    if (   ( inet_pton(AF_INET6, argv[1], &server_addr.sin6_addr) )  <0 ) {
        perror("inet_pton");
        return 1;
    }


  s = socket(AF_INET6, SOCK_STREAM, 0);
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(5000);
    inet_pton(AF_INET6, "::1", &addr.sin6_addr);
    connect(s, (struct sockaddr *)&addr, sizeof(addr));
    
    

   // печатаю содержимое структуруы server_addr
    printf("sockaddr_in6     : ");
    for (int i = 0; i < sizeof(server_addr); i++) {
        printf("%02x ", ((unsigned char*)&server_addr)[i]  );
    }
    printf("\n");




    // Подключаемся к серверу
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }


    // Закрываем сокет
    close(sockfd);
    return 0;
}

