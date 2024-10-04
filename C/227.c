#include <stdio.h>
//#include <arpa/inet.h>
#include <unistd.h>


void main();




void main() {

    char host[16];
    int s = gethostname( host, 16); 
    printf (" hostname = %s \n", host );


}




