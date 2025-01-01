#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() {
    // Открываем /dev/zero
    int fd = open("/dev/zero", O_RDONLY);
    if (fd < 0) {
        perror("error open");
        return 1;
    }
    printf("Открыли файл /dev/zero\n");

    // Мапим файл в память
    void *addr = mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("error mmap");
        close(fd);
        return 1;
    }
    printf("Создали memory mapping для /dev/zero и ждем 30с\n");
    sleep(30);

    // Закрываем файл, но маппинг остаётся
    close(fd);
    printf("Закрыли файл /dev/zero\n");

    // Ждём, чтобы успеть проверить с lsof
    printf("Спим 30 секунд. Проверяйте с lsof...\n");
    sleep(30);

    // Освобождаем memory mapping
    munmap(addr, 4096);
    printf("Освободили memory mapping\n");

    // Спим ещё, чтобы проверить, что всё чисто
    sleep(30);

    return 0;
}


