#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#define TIME_DELAY 160

int main() {

    ssize_t rr;
    unsigned int td = TIME_DELAY;
    int flag;
    socklen_t len = sizeof(flag);

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }


    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 ){
           perror("aton error");
           return 1;
    };
   if ( connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))  <0 ){
          perror("connect error \n");
          return 1;
   };


    // Получение состояния TCP_NODELAY
    if (getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, &len) < 0) {
        perror("getsockopt TCP_NODELAY");
        exit(EXIT_FAILURE);
    } else {
       printf("TCP_NODELAY OFF\n");
      }


    // Получение состояния TCP_CORK
    if (getsockopt(sockfd, IPPROTO_TCP, TCP_CORK, &flag, &len) < 0) {
        perror("getsockopt TCP_CORK");
        exit(EXIT_FAILURE);
    } else {
       printf("TCP_CORK OFF\n");
      }


   printf("TCP Client running \n" );

   sleep(10);

   char buff[500];
   memset(buff, 1, sizeof(buff));
   buff[500] = 0x00;
   
   for (int j=0; j<5; j++){
        rr = write(sockfd, &buff, sizeof(buff));
	printf("отослано %i байтов\n", rr);
	}

   printf("сплю %iс\n", td);
   sleep(td);

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










