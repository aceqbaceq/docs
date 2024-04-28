#include <stdio.h>

int main () {

   int  var1 = 500;
   printf( "var1 = %i\n", var1  );


   int *pVar1;
   pVar1 = &var1;
   printf( "Address of var1 variable in memory(hex) =  %p bytes\n", pVar1  );
   printf( "Address of var1 variable in memory(dec) =  %li bytes\n", ( long int ) pVar1  );
   printf( "Address of var1 variable in memory(dec) =  %li TB\n",( ( long int ) pVar1 ) /1024 /1024 /1024 /1024);


   printf( "var1 = %i\n", *pVar1 );


   char var2 = 'a';
   printf ( "var2=%c\n", var2 );
   printf ( "var2=%d\n", ( int ) var2 );






   return 0;
}
