#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 1024*1024*1024

int main() {
    // Открываем /dev/zero
    int fd = open("/dev/zero", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Маппируем его в память с флагом MAP_SHARED
    void *p = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Клонируем процесс
    pid_t pid = fork();
    
    if (pid == 0) {
        // Дочерний процесс
        printf("Child process: Before memset, first byte: 0x%02x\n", *(unsigned char*)p);
        memset(p, 0x10, SIZE); // Записываем 0x10 в первый байт
        printf("Child process: After memset, first byte: 0x%02x\n", *(unsigned char*)p);
        sleep(120);
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        // Родительский процесс
        sleep(3);  // Ждем, чтобы дочерний процесс успел записать
     volatile unsigned char *volatile_ptr = (volatile unsigned char *)p;
        for (size_t i = 0; i < SIZE; i++) {
            volatile_ptr[i]; // Чтение данных для их активации
        }
        sleep(120);
        close(fd);
    }

    return 0;
}


