#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    void *current_brk, *new_brk;

    sleep (30);
    // Получаем текущий конец кучи
    current_brk = sbrk(0);
    printf("Текущий конец кучи: %p\n", current_brk);

    // Увеличиваем конец кучи на 1 страницу (обычно 4096 байт)
    new_brk = sbrk(10*4096);
    if (new_brk == (void *) -1) {
        perror("Ошибка при увеличении кучи");
        return 1;
    }

    // Выводим новый конец кучи
    printf("Новый конец кучи: %p\n", new_brk);

    sleep (20);


    // Увеличиваем конец кучи на 1 страницу (обычно 4096 байт)
    new_brk = sbrk(100*4096);
    if (new_brk == (void *) -1) {
        perror("Ошибка при увеличении кучи");
        return 1;
    }


    // Выводим новый конец кучи
    printf("Новый конец кучи: %p\n", new_brk);

     sleep (20);

    printf("выхожу!.\n");

    return 0;
}


