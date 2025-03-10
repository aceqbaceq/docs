#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int main() {
    int fd;
    struct termios term;

    // Открываем терминал (например, /dev/tty1 или /dev/pts/0)
    fd = open("/dev/tty4", O_RDWR);
    if (fd == -1) {
        perror("Error opening terminal");
        return 1;
    }

    // Получаем текущие параметры терминала
    if (tcgetattr(fd, &term) == -1) {
        perror("Error getting terminal attributes");
        close(fd);
        return 1;
    }

    // Включаем канонический режим (если он был выключен)
    term.c_lflag |= ICANON;

    // Отключаем режим передачи EOF (например, ^D) из команды ctrl-D
    term.c_lflag &= ~ECHO;

    // Применяем изменения к терминалу
    if (tcsetattr(fd, TCSANOW, &term) == -1) {
        perror("Error setting terminal attributes");
        close(fd);
        return 1;
    }

    printf("Terminal settings changed successfully.\n");

    // Закрываем терминал
    close(fd);

    return 0;
}


