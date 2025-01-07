#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 256

int main() {
    // Открытие очереди сообщений для чтения
    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(1);
    }

    // Буфер для получения сообщения
    char buffer[MAX_SIZE];
    
    // Чтение сообщения
    ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
    if (bytes_read == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Process 2: Received message: %s\n", buffer);

    // Закрытие очереди
    mq_close(mq);

    // Удаление очереди
    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(1);
    }

    return 0;
}


