#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MSGSIZE 12  


int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 ){
           perror("aton error");
           return 1;
    };

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    printf("UDP Server running.\n");


    char buffer[MSGSIZE];
    memset(buffer, 0, sizeof(buffer));
    ssize_t rv;

for (int j=0; j<2; j++){
    if (   (rv = recv(sockfd, &buffer, sizeof(buffer-1), MSG_TRUNC|MSG_WAITALL))  < 0  ){
         perror("recv error");
    };
    buffer[MSGSIZE-1] = 0x00;
    printf("\nRead datagram from kernel\n");
    printf("the message is  %s \n", buffer);
    printf("the length of the the message is  %i \n", strlen(buffer));
    printf("Original datagram Size = %i bytes.\n", rv);

}

    pause();  // Ожидаем завершения
    close(sockfd);
    return 0;
}



