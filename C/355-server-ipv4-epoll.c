#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_EVENTS 1


void make_socket_non_blocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
}



void handle_client(int c, int pid)
{
    char buf[8192];
    char *lastpos;
    int size;

    while (1) {
        size = recv(c, buf, 8192, 0);
        if (size == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // Нет больше соединений
                    break;
            }
        }
        if (size == 0) {
            break;
        }
        dprintf(c, "pid = %i | ", pid);
        lastpos = strchr(buf, '\n');
        send(c, buf, lastpos+1-buf, 0);
    }
}



int main() {
    int s;
    int c;
    int reuseaddr = 1;
    struct sockaddr_in addr;
    int pid;
    socklen_t addr_len;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ){
        perror("не удалось создать сокет");
    };
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_len = sizeof(addr);

    if ( bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0  ){
         perror("не удалось сделать bind");
    };
    
    listen(s, 5);


    // Создаем epoll инстанс
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }


    // Создаем две переменные одну для сования дескриптороа в ядро
    // а вторую для получения ответа из ядра
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];


    // Добавляем дескриптор сокета  в еполл инстанс  плюс  EPOLLIN 
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = s;  // Файл
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, s, &event) == -1) {
        perror("epoll_ctl: file_fd - EPOLLIN");
        exit(EXIT_FAILURE);
    }






        pid = fork(); // клонируемся
        if (pid == -1) {
            exit(1);
        } 



        while (1) {
    	    int n = epoll_wait(epfd, events, MAX_EVENTS, -1);  // Блокируемся на события
    	    if (n < 0) {
        	 if (errno == EINTR) {
                // Если вызов был прерван сигналом, просто продолжаем цикл
                continue;
                };
    	    perror("epoll_wait");
    	    exit(EXIT_FAILURE);
    	    }



    	    for (int k = 0; k < n; k++) {
        	if (  (events[k].data.fd == s) && (events[k].events & EPOLLIN)   ){
            	    c = accept(s, (struct sockaddr *)&addr, &(addr_len) );
            	    make_socket_non_blocking(c);
                       handle_client(c, pid);
                        close(c);

                    };
                };
                };
                

      close(epfd);
      close(s);
    	    
        if (pid==0){
           printf ("чайлд программа успешно закончила работу \n");

        };
        

        if (pid > 0) {
            waitpid(pid, NULL, 0);
           printf ("парент программа успешно закончила работу \n");

        }


};



