#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>


void main();




void main() {


    char ip6_1[] = "fe80::841b:711d:d728:5950";
    printf (" ip_v6 input = %s \n", ip6_1 );



    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;  // will point to the results


    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET6;       // 
    hints.ai_socktype = SOCK_STREAM;  // 
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me


    if ((status = getaddrinfo(ip6_1, NULL, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
    }

    printf (" size of &(addrinfo->ai_addr) = %i \n", sizeof (*(servinfo->ai_addr)) );


    struct sockaddr_in6 * s_v6 = (struct sockaddr_in6 *) servinfo->ai_addr;

    char ip6_2 [INET6_ADDRSTRLEN];
    const char * p_P1 = inet_ntop (AF_INET6, &(s_v6->sin6_addr), ip6_2, sizeof(ip6_2) );
    printf (" size = %s \n", ip6_2  );




}



