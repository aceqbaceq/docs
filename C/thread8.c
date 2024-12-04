#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Получаем PID процесса, который должен получить сигнал
    printf("Enter the PID of the target process: ");
    scanf("%d", &pid);

    // Отправляем сигнал SIGTERM в целевой процесс
    printf("Sending SIGTERM to process %d...\n", pid);
    kill(pid, SIGTERM);

    return 0;
}


