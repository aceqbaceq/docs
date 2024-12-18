#define _GNU_SOURCE
#include <assert.h>


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>




int main() {

    setbuf(stdout, NULL);
    printf("Текущий конец кучи: \n");


    return 0;
}


