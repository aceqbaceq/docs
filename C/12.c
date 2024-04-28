#include <stdio.h>

int main () {

    int var1 = 1;

    int *pVar1;
    pVar1 = &var1;

    printf( "Address of var1 variable in memory(hex) =  %p bytes\n", (void *) pVar1  );




    long int var2 = 1;

    printf( "Address of var2 variable in memory(hex) =  %p \n", (int *) var2  );



   return 0;
}
