#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    void *current_brk, *new_brk;
    size_t size = 4096; // Размер выделяемой памяти (1 страница)

    // Получаем текущий конец кучи
    current_brk = sbrk(0);
    printf("Текущий конец кучи: %p\n", current_brk);

    // Увеличиваем конец кучи на 1 страницу (4096 байт)
    new_brk = sbrk(size);
    if (new_brk == (void *)-1) {
        perror("Ошибка при увеличении кучи");
        return 1;
    }
    printf("Новый конец кучи: %p\n", new_brk);

    // Инициализируем выделенную память, чтобы ядро выделило физическую память
    char *mem = (char *)new_brk;
    for (size_t i = 0; i < size; i++) {
        mem[i] = 0; // Просто записываем нули в выделенную область памяти
    }

    // Теперь можно безопасно уменьшить конец кучи
    if (brk(current_brk) == -1) {
        perror("Ошибка при сбросе кучи");
        return 1;
    }

    printf("Конец кучи успешно сброшен.\n");

    return 0;
}


