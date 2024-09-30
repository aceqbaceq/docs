#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

void main();




void main() {



    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo("google.com", "http", &hints, &servinfo)) != 0) {
	fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	exit(1);
    }

    

    struct sockaddr  * p_P1 = servinfo->ai_addr;

    struct sockaddr_in* internet_addr = (struct sockaddr_in*) p_P1;

    printf("google.com is at: %s\n", inet_ntoa(internet_addr->sin_addr));





    freeaddrinfo(servinfo); // free the linked-list



}

