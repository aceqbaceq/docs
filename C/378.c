#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>



int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
   if ( connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))  <0 ){
          perror("connect error \n");
          return 1;
   };
   printf("TCP Client running \n" );
   printf("сплю 5с\n");
   sleep(5);
   printf("запускаю shutdown\n");
   if ( shutdown(sockfd, SHUT_RDWR) < 0 ){
         perror ("shutdwn error");
         return 1 ;
   }
   sleep(5);
   close(sockfd);
   printf("close(socket) выполенне\n");
   sleep(90);
   return 0;
}










