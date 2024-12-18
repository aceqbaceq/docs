#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {

    setbuf(stdout, NULL);
    
    int *arr;
    int n = 10;  // Размер массива
    //printf ("размер int = %i \n", sizeof(int));
    printf ("не был запущен ни один маллок\n");

    
    
    // Выделяем память для массива из 10 целых чисел
        arr = (int *)malloc(n * sizeof(int));
    

    // Проверяем, успешно ли была выделена память
    if (arr == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return 1;
    }

    printf ("был запущен 1-ый  маллок\n");
    printf("адрес начала маллок зоны = %p HEX\n", arr);
    



    // Выделяем память для массива из 10 целых чисел
        int *arr_2 = (int *)malloc(n * sizeof(int));
    

    // Проверяем, успешно ли была выделена память
    if (arr_2 == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return 1;
    }

    printf ("был запущен 2-ый  маллок\n");
    printf("адрес начала маллок зоны = %p HEX\n", arr_2);
    




    // Освобождаем память
    free(arr);
    free(arr_2);
    printf("память освобождена успешно\n", arr);

    sleep (120);
    return 0;
}



