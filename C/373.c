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
    // Открытие или создание очереди сообщений
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0666, NULL);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(1);
    }

    // Сообщение для отправки
    char *message = "Hello from Process 1!";
    
    // Отправка сообщения
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Process 1: Message sent: %s\n", message);

    // Закрытие очереди
    mq_close(mq);

    return 0;
}


