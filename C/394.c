#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 1024*1024*1024

int main() {
    int fd;
    char *data;

    // 1. Открытие или создание объекта shared memory
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // 2. Установка размера объекта shared memory
    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // 3. Отображение памяти в адресное пространство
    data = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // 4. Запись в разделяемую память
    printf("Writing to shared memory...\n");
    strncpy(data, "Hello from Process 1!", SHM_SIZE);


    printf("пауза 60с\n");
    sleep(60);


    // 5. Очистка ресурсов
    if (munmap(data, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}


