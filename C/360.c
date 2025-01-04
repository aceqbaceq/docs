#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig) {
    // Просто игнорируем сигнал
    printf("SIGINT был получен, но игнорируется.\n");
}

int main() {
    // Устанавливаем обработчик для SIGINT
    signal(SIGINT, sigint_handler);

    // Бесконечный цикл, чтобы программа не завершалась
    while (1) {
        printf("Программа работает... Нажмите Ctrl+C, чтобы проверить игнорирование SIGINT.\n");
        sleep(1);
    }

    return 0;
}


