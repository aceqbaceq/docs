#include <stdio.h>
#include <stdlib.h>

int main() {
    void *arr;
    size_t size = 4096; // 1 страница памяти

    arr = malloc(size); // Выделяем память
    if (arr == NULL) {
        perror("Ошибка при выделении памяти");
        return 1;
    }

    printf("Память выделена: %p\n", arr);

    // Освобождаем память
    free(arr);
    printf("Память освобождена.\n");

    return 0;
}

