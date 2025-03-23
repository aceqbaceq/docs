#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

int main (){


    int fd=0;
    struct termios term, term_cpy;

/*
    // Открываем текущий терминал 
    fd = open("/dev/tty", O_RDWR);
    if (fd == -1) {
        perror("Error opening terminal");
        return 1;
    }
*/



    // Получаем текущие параметры терминала
    if (tcgetattr(fd, &term) == -1) {
        perror("Error getting terminal attributes");
        close(fd);
        return 1;
    }

    // делаю бекап настроек
    term_cpy=term;
   
    // Выключаем канонический режим (если он был выключен)
    term.c_lflag &= ~ICANON;  // Отключаем ICANON
    //term.c_lflag &= ~ISIG;  // Отключаем ISIG
    //term.c_lflag |= ICANON;

    // Применяем изменения к терминалу
    if (tcsetattr(fd, TCSANOW, &term) == -1) {
        perror("Error setting terminal attributes");
        close(fd);
        return 1;
    }




   system("stty -a");


  int fd2;
  char c;
  while(1){


     fd2 = fgetc(stdin);
       if ( fd2 ==  EOF ){
           perror ("\nполучил EOF!");
           // восстанавливаю настройки термиала
           tcsetattr(fd, TCSANOW, &term_cpy);
           return 0;
           }

/*
       if ( fd2 ==  0x3 ){
           perror ("\nя получил Ctrl+C!");
           // восстанавливаю настройки термиала
           tcsetattr(fd, TCSANOW, &term_cpy);
           return 0;
           }
*/



     c=(char)fd2;
     dprintf(1,"\nя получил символ! = ");
     write(1, &c, sizeof(c) );
     dprintf(1,"\n");

  }

  close (fd2);


return 0;

}


