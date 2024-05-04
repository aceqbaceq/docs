
#include <stdio.h>
#include <stdlib.h>




int square( unsigned char  );


int  main() {


   unsigned char c1 = 9;
   unsigned char b1 = 0;
   b1 = square(c1);
   printf ("b1 = %hhu\n", b1);




  exit(0);
}


int square (unsigned char a ) {

    printf ("I am inside square function, argument a = %hhu\n", a);
    unsigned char sq = a * a;



  return(sq);
}


