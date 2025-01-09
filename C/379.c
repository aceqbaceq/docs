#define _GNU_SOURCE
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


// Глобальная переменная для хранения pid дочернего процесса
pid_t child_pid = -1;
int epfd = -1;  // Глобальная переменная для epoll-дескриптора
sem_t *sem;
pid_t s = -1; // перемннная для сокета



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



    // Завершаем дочерний процесс, если он существует
    if (  (child_pid > 0)  &&  (getpid() != child_pid)  ){
        kill(child_pid, SIGINT);
        waitpid(child_pid, NULL, 0);  // Ожидаем завершения дочернего процесса
    }



    const char *message1 = "закрываем epfd...\n";
    write(STDOUT_FILENO, message1, strlen(message1));  // Используем write вместо printf

    // Закрываем epoll-дескриптор, если он открыт
    if (epfd != -1) {
        close(epfd);
    }


    // Закрываем семафор
        sem_close(sem);
        sem_unlink("/my_semaphore"); // Удаляем семафор


    // закрыаем сокет
    close(s);
    
    exit(0);  // Завершить процесс с кодом успеха

}






int check_socket_non_blocking(int sockfd) {

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    // Проверяем, установлен ли флаг O_NONBLOCK
    if (flags & O_NONBLOCK) {
        printf("Сокет  %i в O_NONBLOCK режиме \n", sockfd);
    } else {
        printf("ПРОБЛЕМА: Сокет  %i в блокирубщем режиме .\n", sockfd);
        return 1;
    }





}






void handle_client(int z)
{
    char buf[8192];
    char *lastpos;

    while (1) {
        ssize_t n  = recv(z, buf, sizeof(buf), 0);
        if (n > 0) {
            // Данные успешно прочитаны
            dprintf(z, "pid = %i | ", getpid());
            lastpos = strchr(buf, '\n');
            send(z, buf, lastpos+1-buf, 0);
            
             if (epoll_ctl(epfd, EPOLL_CTL_DEL, z, NULL) == -1) {
             perror("epoll_ctl: EPOLL_CTL_DEL");
             exit(EXIT_FAILURE);
             };
             if (is_fd_valid(z) == 1) {
                printf("закрываю tcp содеинение с этой стороны\n");
                close(z);
              } else {
                  printf("Дескриптор %d уже закрыт.\n", z);
              }
             break;

            
        }  else if (n == 0) {
             // Другая сторона закрыла соединение
             printf("Соединение закрыто другой стороной.\n");
             if (epoll_ctl(epfd, EPOLL_CTL_DEL, z, NULL) == -1) {
             perror("epoll_ctl: EPOLL_CTL_DEL");
             exit(EXIT_FAILURE);
             };
             if (is_fd_valid(z) == 1) {
                close(z);
              } else {
                  printf("Дескриптор %d уже закрыт.\n", z);
              }
             break;
        } else {
            // Ошибка
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // Данных нет (это нормально для неблокирующего сокета)
                break;
            } else {
                // Ошибка соединения
                perror("Ошибка в recv");
            if (epoll_ctl(epfd, EPOLL_CTL_DEL, z, NULL) == -1) {
            perror("epoll_ctl: EPOLL_CTL_DEL");
            exit(EXIT_FAILURE);
            };
             if (is_fd_valid(z) == 1) {
                close(z);
              } else {
                  printf("Дескриптор %d уже закрыт.\n", z);
              }
            break;
            }
        }
    } // while END


}  // function END







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



  // Создаем POSIX семафор с именем "/my_semaphore", инициализируем значением 1
   key_t key = 0x512f140a;

    
   int semid = semget(key, 0, 0);  // Мы не собираемся создавать новый, только проверяем существующий
    if (semid == -1) {
        if (errno == ENOENT) {
            // Семафор с таким ключом не существует
            //printf("Semaphore does not exist.\n");

        } else {
            // Ошибка при вызове semget (например, проблема с правами доступа)
            perror("semget");
        }
    } else {
        // Семафор с таким ключом существует
        printf("Semaphore exists with ID: %d\n", semid);
        // Удаляем семафор
       if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        return 1;
    }  
    }


            sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0644, 1);
               if (sem == SEM_FAILED) {
                  perror("Не удалось создать семафор");
                  exit(EXIT_FAILURE);
            }



    
    



    int c;
    int reuseaddr = 1;
    struct sockaddr_in addr;
    socklen_t addr_len;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ){
        perror("не удалось создать сокет");
    };
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    addr.sin_addr.s_addr = INADDR_ANY;

    addr_len = sizeof(addr);

    if ( bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0  ){
         perror("не удалось сделать bind");
    };
    
    listen(s, 5);





        child_pid = fork(); // клонируемся
        if (child_pid == -1) {
            exit(1);
        } 





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


            //printf("я в цикле после epoll_wait , pid = %i, n = %i\n", getpid(), n);
    	    for (int k = 0; k < n; k++) {
        	if (  (events[k].data.fd == s) && (events[k].events & EPOLLIN)   ){
                   //printf("я в цикле после epoll_wait pid = %i, дескриптор = %i\n", getpid(), s);


                   if (sem_trywait(sem) == 0) {
                   // Семафор захвачен успешно
                   //printf("Процесс %d захватил семафор\n", getpid());

            	    c = accept4(s, (struct sockaddr *)&addr, &(addr_len), SOCK_NONBLOCK );
            	    if (c == -1) {
                        perror("Ошибка при принятии соединения");
                        continue; // Продолжить цикл, если произошла ошибка
                        } 
                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = c;  // Файл
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, c, &event) == -1) {
                          perror("epoll_ctl: file_fd - EPOLLIN");
                          exit(EXIT_FAILURE);
                    }
            	    if ( check_socket_non_blocking(c) == 1) {
                          printf("ошибка с сокетом %i, не получается устаноить O_NONBLOCK режим\n");
                          return 1;
            	    };
                    handle_client(c);

        //printf("Процесс %d завершил работу и освободил семафор\n", getpid());
        sem_post(sem); // Освобождаем семафор

    } else if (errno == EAGAIN) {
        // Семафор занят
        //printf("Процесс %d не смог захватить семафор (занят)\n", getpid());
        break;
    } else {
        // Ошибка при попытке захватить семафор
        perror("Ошибка при захвате семафора");
        break;
    }



                }; //if END
               
  
                if (  (events[k].data.fd != s) && (events[k].events & EPOLLIN)   ) {
                     printf("я  цикле после epoll_wait pid = %i, дескриптор  = %i\n", getpid(), events[k].data.fd);
                     int result = is_fd_valid(events[k].data.fd);
                       if (result == 1) {
                           printf("pid = %i, Дескриптор %d существует.\n", getpid(), events[k].data.fd);
                           handle_client(events[k].data.fd);
                          } else if (result == 0) {
                            printf("pid = %i, Дескриптор %d не существует.\n", getpid(), events[k].data.fd);
                            break;
                          } else {
                                printf("Произошла ошибка при проверке дескриптора %d.\n", events[k].data.fd);
                                break;
                          }


                };  //if END




            }; //for END



    }; //while END
                

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

    // Закрываем семафор
        sem_close(sem);
        sem_unlink("/my_semaphore"); // Удаляем семафор
    	    
        if (child_pid==0){
           printf ("чайлд программа успешно закончила работу \n");

        };
        

        if (child_pid > 0) {
            waitpid(child_pid, NULL, 0);
           printf ("парент программа успешно закончила работу \n");

        }


};



