#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 3  // Число рабочих потоков

// Флаг для сигналов
volatile sig_atomic_t signal_received = 0;  

// Потоковая функция
void* thread_func(void* arg) {
    int thread_id = *((int*)arg);
    sigset_t set;

    // Блокируем сигнал SIGTERM в этом потоке
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // Устанавливаем обработчик сигнала только в этом потоке
    struct sigaction sa;
    sa.sa_handler = NULL;  // Без действия в случае SIGTERM
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);  // Не блокируем другие сигналы
    sigaction(SIGTERM, &sa, NULL);

    // Каждый поток будет работать до получения сигнала
    while (1) {
        printf("Thread %d is running...\n", thread_id);
        sleep(1);  // Эмуляция работы

        // Если сигнал получен, завершаем этот поток
        if (signal_received) {
            printf("Thread %d received signal, exiting...\n", thread_id);
            pthread_exit(NULL);  // Завершаем текущий поток
        }
    }

    return NULL;
}

// Обработчик сигнала, который будет сигнализировать о завершении потока
void signal_handler(int sig) {
    signal_received = 1;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Устанавливаем глобальный обработчик сигнала
    signal(SIGTERM, signal_handler);

    // Создаем рабочие потоки
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_ids[i]);
    }

    // Даем потокам время на работу
    sleep(3);  // Потоки будут работать 3 секунды

    printf("Main process running...\n");

    // Отправляем сигнал SIGTERM другому процессу (или самому себе)
    // В реальном случае сюда будет послан сигнал из другого процесса.
    printf("Sending SIGTERM to process...\n");
    kill(getpid(), SIGTERM);  // Отправляем сигнал всему процессу

    // Ожидаем завершения потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread finished.\n");
    return 0;
}


