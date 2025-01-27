#define _GNU_SOURCE
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MEMFD_NAME "my_memfd_example"

int main() {
    // Создаем memfd-объект
    int fd = memfd_create(MEMFD_NAME, MFD_ALLOW_SEALING);
    if (fd == -1) {
        perror("memfd_create");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем размер файла
    size_t mem_size = 1024 * 1024 * 1024; 
    if (ftruncate(fd, mem_size) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }




 // Создаем буфер для записи
    size_t buffer_size = 4096; // 4 KB (обычно соответствует размеру страницы памяти)
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("malloc");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Заполняем буфер значением 0x10
    memset(buffer, 0x10, buffer_size);


    // Пишем буфер в файл, пока не заполним весь файл
    printf("начинаю ПИСАТЬ в файл\n");
    size_t bytes_written = 0;
    while (bytes_written < mem_size) {
        size_t to_write = (mem_size - bytes_written < buffer_size) ? (mem_size - bytes_written) : buffer_size;
        ssize_t written = write(fd, buffer, to_write);
        if (written == -1) {
            perror("write");
            free(buffer);
            close(fd);
            exit(EXIT_FAILURE);
        }
        bytes_written += written;
    }
    printf("закончил ПИСАТЬ в файл\n");
    
    printf("пауза 120с \n");
    sleep(120);


    // Закрываем файловый дескриптор
    close(fd);

    return 0;
}


