#define _GNU_SOURCE      
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define TIME1 0
#define TIMEOUT 600
#define SIZE 1024*1024*10


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
    //char *mapped = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    char *mapped = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Ошибка отображения файла в память");
        close(fd);
        return 1;
    }


    // создаю копию
    //fork();

    // ждем
    printf("жду %iс перед доступом к ммап паяти \n", TIME1);
    sleep(TIME1);


/*
    // достуе к  данные
    printf("приступаю к  ЧТЕНИЮ  ммап памяти \n");
    char data;
    for (size_t i = 0;   i < filesize/sizeof(char);   i++ ) {  
        data =  *(mapped+i)      ;  

    }
    printf("ЧТЕНИЕ  ЗАКОНЧЕНО \n");
*/

    
    //
    printf("приступаю к  ЗАПИСИ  ммап памяти \n");
    //memset(mapped, 0x44, SIZE);
    for (size_t i = 0;   i < SIZE/sizeof(char);   i++ ) {  
        *(mapped+i) = 0x10      ;

    }
    printf("ЗАПИСЬ  законечена \n");
    

    // ждем
    printf ("теперь sleep %i sec    \n", TIMEOUT);
    sleep(TIMEOUT);



    // Освобождаем отображение и закрываем файл
    munmap(mapped, filesize);
    close(fd);



    return 0;
}

