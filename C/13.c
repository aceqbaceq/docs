#include <stdio.h>
#include <unistd.h>

int main () {

    int klava = 0;

    void * bufer;
    char k[1];
    bufer = &k;

    printf ( "void address = %p\n", bufer );

    size_t count;
    count = 1;

    read( klava, bufer, count);



   printf ( "ti vvel s klavi %c\n", *(char *) bufer );

   char * vasya;
   vasya = (char *) bufer;

   printf ( "ti vvel s klavi %c\n", *vasya );

   return 0;
}

