#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>


int main() {

    socklen_t addr_len;
    int flag;
    socklen_t len = sizeof(flag);
    ssize_t rr = 1;
    char buff[2048];
    int c;
    int reuseaddr = 1;


    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }


    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));


    struct sockaddr_in addr;
    addr_len = sizeof(addr);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 5);

while(1) {
    c = accept4(sockfd, (struct sockaddr *)&addr, &addr_len, 0 );
    if (c == -1) {
                   perror("Ошибка при принятии соединения");
                    return 1;
                        }


    // Получение состояния TCP_NODELAY
    if (getsockopt(c, IPPROTO_TCP, TCP_NODELAY, &flag, &len) < 0) {
        perror("getsockopt TCP_NODELAY");
        exit(EXIT_FAILURE);
    } else {
       printf("TCP_NODELAY OFF\n");
      }


    // Получение состояния TCP_CORK
    if (getsockopt(c, IPPROTO_TCP, TCP_CORK, &flag, &len) < 0) {
        perror("getsockopt TCP_CORK");
        exit(EXIT_FAILURE);
    } else {
       printf("TCP_CORK OFF\n");
      }

    printf("Server running. Press Ctrl+C to stop.\n");
    
    memset(buff, 0, sizeof(buff));
    while(1){
	        rr = read(c, &buff, sizeof(buff));
		if ( rr == 0) {
        		printf("конект завершен на той стороне\n");
        		close(c);
        		break;
                	} else if ( rr > 0) {
                	    printf("получено из сокета %i байтов\n", rr);
                	    sleep(10);
                	  } else {
                		perror ("read error\n");
                		return 1;
                	    }


    }; //while END
    
    
    
}; //END while


    close(sockfd);
    printf("конец программы нажми Ctrl+C\n");
    pause();  // Ожидаем завершения


    return 0;
}


