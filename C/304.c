#include <stdio.h>
# define _POSIX_C_SOURCE 200809L
#include <unistd.h>


int main() {
    if (stdin == NULL) {
        dprintf(1,"stdin is not open\n");

    } else {
    
        dprintf(1,"stdin is open, stdin pointer хранится в %p  а указывает он на адрес  %p\n", (void*) &stdin, stdin);
    }

    if (stdout == NULL) {
        dprintf(1,"stdout is not open\n");
    } else {
        dprintf(1,"stdout is open\n");
    }

    if (stderr == NULL) {
        dprintf(1,"stderr is not open\n");
    } else {
        dprintf(1,"stderr is open\n");
    }

   sleep (60);

    return 0;
}



