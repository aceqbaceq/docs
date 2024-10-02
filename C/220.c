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

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(NULL, "4678", &hints, &servinfo)) != 0) {
	fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	exit(1);
    }


    struct addrinfo  * current;

    for(current = servinfo; current != NULL; current = current->ai_next) {
        struct sockaddr  * p_P1 = current->ai_addr;
        struct sockaddr_in* internet_addr = (struct sockaddr_in*) p_P1;
        short unsigned int port = internet_addr->sin_port;  
        printf("IP is at: %s, port = %hu \n", inet_ntoa(internet_addr->sin_addr), ntohs (port)  );
        printf ("===============\n");
        
    }

   
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    listen (sockfd, 3);


    socklen_t addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    getsockname(sockfd, (struct sockaddr *)&addr, &addr_size);
        short unsigned int port = addr.sin_port;  
        printf("IP is at: %s, port = %hu \n", inet_ntoa(addr.sin_addr), ntohs (port)  );



   sleep (60);

    freeaddrinfo(servinfo); // free the linked-list



}

