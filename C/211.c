#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

void main();




void main() {



// 
char ip2 [INET_ADDRSTRLEN] = "23.24.25.26";
printf( "ipv4 = %s\n", ip2 );  


struct in_addr ia2;
inet_pton(AF_INET, ip2, &ia2);


printf( "ipv4 = %s\n", inet_ntoa(ia2) );  
printf ("============\n");




}


