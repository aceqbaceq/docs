#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>




int main() {
    void *current_brk, *new_brk;


    //setbuf(stdout, NULL); 

    // Получаем текущий конец кучи
    current_brk = sbrk(0);
    dprintf(1,"Текущий конец кучи: %p\n", current_brk);

    // Увеличиваем конец кучи на 1 страницу (обычно 4096 байт)
    new_brk = sbrk(4096);
    if (new_brk == (void *) -1) {
        perror("Ошибка при увеличении кучи");
        return 1;
    }

    // Выводим новый конец кучи
    dprintf(1,"Новый конец кучи: %p\n", new_brk);

//    sleep (60);




    // Используем brk() для изменения конца кучи
    if (brk(current_brk) == -1) {
        perror("Ошибка при сбросе кучи");
        return 1;
    }



    dprintf(1,"Конец кучи сброшен обратно.\n");

    sleep (60);

    return 0;
}


