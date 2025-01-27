#define _GNU_SOURCE      
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define TIMEOUT 600
#define GB_1 1024*1024*1024


int main() {
    const char *filename = "/home/noroot/VM/fake/ub18.img";  // Имя файла для отображения

    // Открываем файл 
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Получаем размер файла
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == -1) {
        perror("Ошибка получения размера файла");
        close(fd);
        return 1;
    }

    // Отображаем файл в память
    char *mapped = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Ошибка отображения файла в память");
        close(fd);
        return 1;
    }


    // ждем
    sleep(5);



    // ждем
    printf ("sleep %i sec    \n", TIMEOUT);
    sleep(TIMEOUT);



    // Освобождаем отображение и закрываем файл
    munmap(mapped, filesize);
    close(fd);



    return 0;
}

