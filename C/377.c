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
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#define MAX_EVENTS 3


int epfd = -1;  // Глобальная переменная для epoll-дескриптора
pid_t s  = -1;  // перемннная для сокета



int is_fd_valid(int fd) {
    // Проверяем, является ли дескриптор файла валидным
    if (fcntl(fd, F_GETFD) == -1) {
        if (errno == EBADF) {
            // Дескриптор не существует или недействителен
            return 0;  // Дескриптор не существует
        } else {
            // Произошла другая ошибка
            perror("fcntl");
            return -1;  // Ошибка при проверке
        }
    }
    // Дескриптор существует
    return 1;
}





void handle_sigint(int sig) {

    const char *message = "Получен сигнал SIGINT. Завершаем работу...\n";
    write(STDOUT_FILENO, message, strlen(message));  // Используем write вместо printf


    const char *message1 = "закрываем epfd...\n";
    write(STDOUT_FILENO, message1, strlen(message1));  // Используем write вместо printf


    // Закрываем epoll-дескриптор, если он открыт
    if (epfd != -1) {
        close(epfd);
    }


    // закрыаем сокет
    close(s);
    
    exit(0);  // Завершить процесс с кодом успеха

}












int main() {

    
    // Устанавливаем обработчик для SIGINT
    struct sigaction sa;
    sa.sa_handler = handle_sigint;  // Функция-обработчик
    sigemptyset(&sa.sa_mask);       // Не блокируем другие сигналы
    sa.sa_flags = 0;                // Без дополнительных флагов

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Не удалось установить обработчик SIGINT");
        exit(EXIT_FAILURE);
    }









    int c;
    int reuseaddr = 1;
    struct sockaddr_in addr;
    socklen_t addr_len;

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( s < 0 ){
        perror("не удалось создать сокет");
    };
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(addr);

    if ( bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0  ){
         perror("не удалось сделать bind");
    };
    
    listen(s, 5);










    // Создаем epoll инстанс
    epfd = epoll_create1(0);
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





for (int j=0; j<2; j++){
    	    int n = epoll_wait(epfd, events, MAX_EVENTS, -1);  // Блокируемся на события
    	    if (n < 0) {
        	 if (errno == EINTR) {
                // Если вызов был прерван сигналом, просто продолжаем цикл
                //continue;
                };
    	    perror("epoll_wait");
    	    exit(EXIT_FAILURE);
    	    }



    	    for (int k = 0; k < n; k++) {

    	        // обработка слушающего сокета
        	if (  (events[k].data.fd == s) && (events[k].events & EPOLLIN)   ){
            	    c = accept(s, (struct sockaddr *)&addr, &(addr_len) );
            	    if (c == -1) {
                        perror("Ошибка при принятии соединения");
                        return 1; 
                        } 
		printf("входящее содеиениени зафиксировано! дескрипотор = %i \n", c);
                    event.events =  EPOLLRDHUP | EPOLLET;
                    event.data.fd = c;  // Файл
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, c, &event) == -1) {
                          perror("epoll_ctl: file_fd - EPOLLIN");
                          exit(EXIT_FAILURE);
            	    }


                }; //if END
               
  
                // обработка рабочего сокета
                if (  (events[k].data.fd != s) && (events[k].events &  EPOLLRDHUP)   ) {
                     int result = is_fd_valid(events[k].data.fd);
                     if (result == 1) {
                           printf("получено событие о том что удаленный пир закрыл конект\n");
                           printf("удаяляю Дескриптор %d из epoll\n", events[k].data.fd);
                           if (epoll_ctl(epfd, EPOLL_CTL_DEL, events[k].data.fd, NULL) == -1) {
                                   perror("epoll_ctl: EPOLL_CTL_DEL");
                                   exit(EXIT_FAILURE);
                           };

                           printf("жду 30 с и закрываю сокет\n");
                           sleep(30);
                           if (shutdown(events[k].data.fd, O_RDWR) < 0 ){
                    		    perror("shutdown\n");
                    	   };
                    	   close( (events[k].data.fd) );
                    	   printf("дескрипттор %d закрыт\n", events[k].data.fd);
                     } else if (result == 0) {
                            printf("pid = %i, Дескриптор %d не существует.\n", getpid(), events[k].data.fd);
                            break;
                     } else {
                                printf("Произошла ошибка при проверке дескриптора %d.\n", events[k].data.fd);
                                break;
                     }


                };  //if END



            }; //for END

}; //END FOR




           // зарвыаем еполл инстанс
             if (is_fd_valid(epfd) == 1) {
                close(epfd);
              } else {
                  printf("Дескриптор %d уже закрыт.\n", epfd);
              }
      
            // закрываем сокет
             if (is_fd_valid(s) == 1) {
                close(s);
              } else {
                  printf("Дескриптор %d уже закрыт.\n", s);
              }



};



