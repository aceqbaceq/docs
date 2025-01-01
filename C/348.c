#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main() {
    struct stat st;

    // Сохраняем информацию о текущем корне (до chroot)
    if (stat("/", &st) == -1) {
        perror("stat on /");
        return 1;
    }
    printf("Before chroot: root inode = %lu\n", st.st_ino);

    // Делаем chroot в /tmp
    if (chroot("/tmp") == -1) {
        perror("chroot to /tmp failed");
        return 1;
    }

    // Переходим в новый корень, чтобы избежать путаницы
    if (chdir("/") == -1) {
        perror("chdir to new root failed");
        return 1;
    }

    // Проверяем inode текущей директории (.)
    if (stat(".", &st) == -1) {
        perror("stat on .");
        return 1;
    }
    printf("After chroot: current directory inode = %lu\n", st.st_ino);

    // Проверяем inode для родительской директории (..)
    if (stat("..", &st) == -1) {
        perror("stat on ..");
        return 1;
    }
    printf("After chroot: parent directory inode = %lu\n", st.st_ino);

    return 0;
}


