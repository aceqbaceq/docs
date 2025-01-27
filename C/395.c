#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SHM_SIZE 1024*1024*1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *data;

    // 1. Создание сегмента памяти
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // 2. Присоединение сегмента памяти
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // 3. Запись в разделяемую память
    printf("Writing to shared memory...\n");
    memset(data, 0x10, SHM_SIZE);


printf("пауза 120с\n");
sleep(120);


    // 4. Отключение от разделяемой памяти
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }


// Удаление сегмента памяти
if (shmctl(shmid, IPC_RMID, NULL) == -1) {
    perror("shmctl");
    exit(1);
}


    return 0;
}


