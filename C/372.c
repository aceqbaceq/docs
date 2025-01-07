#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>

int main() {
    key_t key = ftok("/tmp", 'A'); // Генерация ключа (можно указать любой путь и уникальный символ)
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int semid = semget(key, 2, 0666 | IPC_CREAT); // Создаём массив из 2 семафоров с правами 0666
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore ID: %d\n", semid);


    sleep(60);
    return 0;
}

