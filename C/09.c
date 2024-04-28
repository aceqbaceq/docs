#include <stdio.h>

int main () {

   int  var1 = 500;
   int *pVar1 = &var1;


   printf("Address of var1 variable: %p\n", (void * ) pVar1  );

printf( "var1=%d\n", var1 );
printf( "octal form=%#o\n", var1 );
printf( "hex form=%#x\n", var1 );
printf( "HEX form=%#X\n", var1 );

printf ( "\n"  );


float var2 = 600.5;
printf( "var2=%f\n", var2 );
printf( "var2=%#A\n", var2 );
printf( "var2=%#a\n", var2 );
printf( "var2=%#g\n", var2 );
printf( "var2=%i\n", ( int ) var2 );


long int var3;



   return 0;
}
