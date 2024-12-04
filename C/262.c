#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define MAX_EVENTS 10

int main() {


   // открываем файл с диска
    int file_fd = open("/home/noroot/temp/nc/fifo1", O_RDONLY);
    if (file_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }



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




    // Добавляем fd/0 плюс  EPOLLIN и\или EPOLLHUP в  ядро
      event.events = EPOLLIN|EPOLLHUP;  
    event.data.fd = file_fd;  // Файл
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, file_fd, &event) == -1) {
        perror("epoll_ctl: file_fd - EPOLLIN");
        exit(EXIT_FAILURE);
    }







    // Ожидаем событий
    while (1) {
        int n = epoll_wait(epfd, events, MAX_EVENTS, -1);  // Блокируемся на события
        if (n == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }


        for (int i = 0; i < n; i++) {
            if (  (events[i].data.fd == file_fd) && (events[i].events & EPOLLIN)   ){
                char buffer[256];
                ssize_t bytes_read = read(file_fd, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("Read from stdin: %s", buffer);
                }
            }


            if (  (events[i].data.fd == file_fd) && (events[i].events & EPOLLHUP)   ){
		     // удаялю его дескрипттор из epoll
		     if (epoll_ctl(epfd, EPOLL_CTL_DEL, file_fd, &event) == -1) {
                        perror("epoll_ctl: file_fd - EPOLL_CTL_DEL");
                        exit(EXIT_FAILURE);
                     }
                     // закрываю файл
		     close(file_fd);

                    // открываю файл заново
                    int file_fd = open("/home/noroot/temp/nc/fifo1", O_RDONLY);
                        if (file_fd == -1) { 
                           perror("open");
                           exit(EXIT_FAILURE);
                        }
                    // добалвяю его десприпторр в epoll
                    event.events = EPOLLIN|EPOLLHUP;
                    event.data.fd = file_fd;
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, file_fd, &event) == -1) {
    				perror("epoll_ctl: file_fd - EPOLLIN");
    				exit(EXIT_FAILURE);
		    }

            }



        }
    }

    close(epfd);
    return 0;
}







