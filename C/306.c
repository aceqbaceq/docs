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
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    printf ("UDP сокет создан успешно \n\n");

    // Закрываем сокет
    close(sockfd);
    return 0;
}

