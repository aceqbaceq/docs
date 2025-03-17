#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {


    struct termios oldt, newt;

    // Get current tty driver settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Turn off  ICANON, ECHO и ECHOCTL
    newt.c_lflag &= ~(ICANON | ECHO | ECHOCTL);

    // Apply new settings to tty driver
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);




    int c;

    printf ("Press 'any key' to print on the display (or Ctrl+D to end the program)\n");

    
    while ((c = getchar()) != 0x04) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            printf("%c", c);
    }



    // restore old settings to tty driver
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\nBye-Bye!\n");

    return 0;




}





