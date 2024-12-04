#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define MAX_EVENTS 10

int main() {
    // Создаем epoll инстанс
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // Создаем структуру epoll_event для добавления файловых дескрипторов
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];

    // Добавляем стандартный ввод (fd = 0) в epoll
    event.events = EPOLLIN;  // Слушаем события на ввод
    event.data.fd = STDIN_FILENO;  // Стандартный ввод
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl: stdin");
        exit(EXIT_FAILURE);
    }

    // Создаем или открываем файл для чтения
    int file_fd = open("test.txt", O_RDONLY);
    if (file_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Добавляем файл в epoll
    event.events = EPOLLIN;  // Слушаем события на ввод
    event.data.fd = file_fd;  // Файл
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, file_fd, &event) == -1) {
        perror("epoll_ctl: file_fd");
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
            if (events[i].data.fd == STDIN_FILENO) {
                char buffer[256];
                ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("Read from stdin: %s", buffer);
                }
            }

            if (events[i].data.fd == file_fd) {
                char buffer[256];
                ssize_t bytes_read = read(file_fd, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("Read from file: %s", buffer);
                }
            }
        }
    }

    close(file_fd);
    close(epfd);

    return 0;
}


