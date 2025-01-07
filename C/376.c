#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>



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
    printf("UDP Client running \n" );


    char buffer1[20] = "123456789ABCDEFGHIJ";
    ssize_t sv;
        sv = sendto(sockfd, &buffer1, sizeof(buffer1), 0, 
                        (struct sockaddr*)&addr, sizeof(addr));
        if ( sv  < 0 ){
	       perror ("send error");
    	       return 1;
        };
    printf("Sent %i bytes, message = %s \n", sv, buffer1 );
    sleep(10);



    char buffer2[20] = "ABCDEFGHIJ123456789";
        sv = sendto(sockfd, &buffer2, sizeof(buffer2), 0, 
                        (struct sockaddr*)&addr, sizeof(addr));
        if ( sv  < 0 ){
	       perror ("send error");
    	       return 1;
        };
    printf("Sent %i bytes, message = %s \n", sv, buffer2 );
    sleep(10);
    




    sleep(1);  // Ожидаем завершения
    close(sockfd);
    return 0;
}




