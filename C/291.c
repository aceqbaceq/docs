#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>




int main() {
    void *current_brk, *new_brk;

    sleep (10);
    printf("первый принтф\n");
    sleep (10);
    
    

    // Получаем текущий конец кучи
    current_brk = sbrk(0);
    printf("Текущий конец кучи: %p\n", current_brk);



    // Увеличиваем конец кучи на 1 страницу (обычно 4096 байт)
    new_brk = sbrk(5*40960);
    if (new_brk == (void *) -1) {
        perror("Ошибка при увеличении кучи");
        return 1;
    }

    // Выводим новый конец кучи
    printf("Новый конец кучи: %p\n", new_brk);

    sleep (10);




    // Используем brk() для изменения конца кучи
    if (brk(current_brk) == -1) {
        perror("Ошибка при сбросе кучи");
        return 1;
    }

    sleep (10);

    printf("Конец кучи сброшен обратно.\n");


    return 0;
}


