#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>


void main();




void main() {



    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;  // will point to the results

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    listen (sockfd, 3);


    socklen_t addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    getsockname(sockfd, (struct sockaddr *)&addr, &addr_size);
        short unsigned int port = addr.sin_port;  
        printf("IP is at: %s, port = %hu \n", inet_ntoa(addr.sin_addr), ntohs (port)  );


   sleep (60);




}

