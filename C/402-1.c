#define _GNU_SOURCE      
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define TIMEOUT 600
#define TIME2 0
#define GB_1 1024*1024*1024


int main() {
    const char *filename = "/home/noroot/VM/fake/ub18.img";  // Имя файла для отображения

    // Открываем файл 
    printf("открываю файл \n");
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }
    printf("открыл файл \n");


    // Получаем размер файла
    printf("вычисялляю размер файла \n");
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == -1) {
        perror("Ошибка получения размера файла");
        close(fd);
        return 1;
    }
    printf("вычислил размер файла \n");


    // Отображаем файл в память
    printf("отображаю файл в память \n");
    char *mapped = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Ошибка отображения файла в память");
        close(fd);
        return 1;
    }
    printf("отобразил файл в память \n");


    // ждем
    printf("жду %i с \n", TIME2);
    sleep(TIME2);


    // копию процесса создаем
    //fork();

    // читаем данные
    printf("читаю данные \n");
    uint64_t data;
    for (size_t i = 0;   i < GB_1/sizeof(uint64_t);   i++ ) {  
        data =  *((uint64_t*)mapped+i)      ;  


    }
    printf("прочитал данные \n");




    // ждем
    printf ("sleep %i sec    \n", TIMEOUT);
    sleep(TIMEOUT);



    // Освобождаем отображение и закрываем файл
    munmap(mapped, filesize);
    close(fd);



    return 0;
}

