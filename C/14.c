#include <stdio.h>
#include <unistd.h>

int main () {

    void * pVasya;
    char a = 'a';
    pVasya = &a;

    printf ( "pointer pVasya = %p\n", pVasya   );

    char * pa;
    pa = (char *) pVasya;

    printf ( "pointer pa = %p\n", pa);

    printf ( "char = %c\n", *pa  );

   return 0;
}

