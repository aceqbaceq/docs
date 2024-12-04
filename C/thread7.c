#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Обработчик сигнала
void signal_handler(int sig) {
    printf("Signal received, exiting thread...\n");
    pthread_exit(NULL);  // Завершаем текущий поток
}

// Потоковая функция
void* thread_func(void* arg) {
    sigset_t set;

    // Блокируем сигнал SIGTERM в этом потоке
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // Устанавливаем обработчик сигнала только в текущем потоке
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);  // Не блокировать другие сигналы
    sigaction(SIGTERM, &sa, NULL);

    // Поток будет работать до получения сигнала
    while (1) {
        printf("Thread is running...\n");
        sleep(1);  // Эмуляция работы
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Создаем два потока
    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    // Даем потоку время на работу
    sleep(3);  // Потоки будут работать 3 секунды

    // Отправляем сигнал SIGTERM потоку 1 (он завершится)
    //printf("Sending SIGTERM signal to process\n");
    //kill(getpid(), SIGTERM);  // Отправляем сигнал всему процессу

    // Ожидаем завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread finished.\n");
    return 0;
}


