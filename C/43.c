#define _POSIX_SOURCE
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  struct termios term;

  if (tcgetattr(STDIN_FILENO, &term) != 0)
    perror("tcgetatt() error");
  else {

    puts("Input mode options:");
    puts("-------------------");
    if (term.c_iflag & BRKINT)
      puts("BRKINT is set");
    else
      puts("BRKINT is not set");
    if (term.c_cflag & PARODD)
      puts("Odd parity is used");
    else
      puts("Even parity is used");
    if (term.c_lflag & ECHO)
      puts("ECHO is set");
    else
      puts("ECHO is not set");

    if (term.c_lflag & INPCK)
      puts("INPCK is set");
    else
      puts("INPCK is not set");

    if (term.c_lflag & IGNBRK)
      puts("IGNBRK is set");
    else
      puts("IGNBRK is not set");

    puts("====================");
    printf("\n");
    puts("Output mode options:");
    puts("--------------------");


    printf("The end-of-file character is x'%02x'\n",
term.c_cc[VEOF]);
  }
}

