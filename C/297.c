#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    int *arr;
    int n = 10;  // Размер массива
    //printf ("размер int = %i \n", sizeof(int));
    printf ("не был запущен ни один маллок\n");
    sleep (10);
    
    
    // Выделяем память для массива из 10 целых чисел
        arr = (int *)malloc(n * sizeof(int));
    

    // Проверяем, успешно ли была выделена память
    if (arr == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return 1;
    }

    printf ("был запущен 1-ый  маллок\n");
    printf("адрес начала маллок зоны = %p HEX\n", arr);
    
    sleep (10);




    // Выделяем память для массива из 10 целых чисел
        int *arr_2 = (int *)malloc(n * sizeof(int));
    

    // Проверяем, успешно ли была выделена память
    if (arr_2 == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return 1;
    }

    printf ("был запущен 2-ый  маллок\n");
    printf("адрес начала маллок зоны = %p HEX\n", arr_2);
    
    sleep (10);




    // Освобождаем память
    free(arr);
    printf("память освобождена успешно\n", arr);

    sleep(20);

    return 0;
}


