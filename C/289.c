#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 10;  // Размер массива

    // Выделяем память для массива из 10 целых чисел
    arr = (int *)malloc(n * sizeof(int));

    // Проверяем, успешно ли была выделена память
    if (arr == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return 1;
    }

    // Инициализируем массив значениями
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;  // Пример: квадрат числа
    }

    // Выводим значения массива
    printf("Массив чисел:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Освобождаем память
    free(arr);

    return 0;
}

