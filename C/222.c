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
    hints.ai_family = AF_INET;       // 
    hints.ai_socktype = SOCK_STREAM;  // 
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo("0.0.0.0", "4444", &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
    }



    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 0);
    bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    listen (sockfd, 3);

/*
    socklen_t addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    getsockname(sockfd, (struct sockaddr *)&addr, &addr_size);
        short unsigned int port = addr.sin_port;  
        printf("IP is at: %s, port = %hu \n", inet_ntoa(addr.sin_addr), ntohs (port)  );

    

    int new_sockfd = accept(sockfd, NULL, NULL);

    if ( write (new_sockfd, "hahaha\n", 7) == -1 ) {
           printf ("error!\n");
           exit (1);
    }


    int new_sockfd2 = accept(sockfd, NULL, NULL);

    if ( write (new_sockfd2, "hahaha2\n", 7) == -1 ) {
           printf ("error!\n");
           exit (1);
    }


*/

   sleep (120);





}



