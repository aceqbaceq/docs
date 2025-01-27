#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define MEMORY_SIZE (1L * 1024 * 1024 * 1024)  // 1 GB

int main() {
    // Выделяем 1 GB памяти с использованием mmap
    void *ptr = mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Инициализируем выделенную память (записываем данные)
    memset(ptr, 0, MEMORY_SIZE);

    // Сделаем небольшую паузу, чтобы дать время системе выделить и закэшировать страницы
    printf("Memory allocated and initialized.\n");
    printf("Press Enter to continue and check page cache...\n");
    getchar();  // Ждем, пока пользователь нажмет Enter


    sleep(60);

    // Освобождаем память
    if (munmap(ptr, MEMORY_SIZE) == -1) {
        perror("munmap failed");
        return 1;
    }

    printf("Memory unmapped and freed.\n");
    return 0;
}


