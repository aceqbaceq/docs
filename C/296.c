#include <stdio.h>
#include <unistd.h>

int main() {
    void *p1, *p2;
    
    // Получаем текущий конец кучи
    p1 = sbrk(0);
    printf("Текущий конец кучи: %p\n", p1);

    // Расширяем кучу на 4096 байт (1 страница)
    p2 = sbrk(4096);
    if (p2 == (void *)-1) {
        perror("Ошибка при расширении кучи");
        return 1;
    }
    printf("Новый конец кучи: %p\n", p2);

    // Используем память между p1 и p2
    char *new_memory = (char *)p1;
    for (int i = 0; i < 1024; i++) {
        new_memory[i] = 'A';  // Заполняем память значениями
    }
    
    // Печатаем данные
//    printf("Данные в новой памяти: %.*s\n", 1024, new_memory);


    return 0;
}


