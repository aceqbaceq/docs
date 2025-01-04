#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>








int main() {

    

int epfd, epfd2 ;



    // Создаем epoll инстанс
    epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }


    // Создаем epoll инстанс
    epfd2 = epoll_create1(0);
    if (epfd2 == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    sleep(60);

   close(epfd);
   close(epfd2);


};



