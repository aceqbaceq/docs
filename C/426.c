#include<sys/types.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

int main(){

   printf ("size of char = %ld, "
           "size of int = %ld, " 
           "size of long int = %ld, "
           "size of long long int = %ld\n ",
            sizeof( char ), sizeof ( int ), sizeof ( long int ), sizeof ( long long int  ) );



   unsigned char cr=0x0a;


   unsigned char i0=0x71;
   write(1, &i0, sizeof(i0));
   write(1, &cr, sizeof (cr));


   unsigned short  i1=0x7172;
   write(1, &i1, sizeof(i1));
   write(1, &cr, sizeof (cr));


   unsigned int  i2=0x71727374;
   write(1, &i2, sizeof(i2));
   write(1, &cr, sizeof (cr));


   long int  i8=0x7877767574737271;
   write(1, &i8, sizeof(i8));
   write(1, &cr, sizeof (cr));


   unsigned char c10[10] = { 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A };
   write(1, &c10, sizeof(c10));
   write(1, &cr, sizeof (cr));

   char *str1="qrstuvwxyz";
   write(1, str1, strlen(str1));
   write(1, &cr, sizeof (cr));

   write(1, str1, 1);
   write(1, &cr, sizeof (cr));
   write(1, str1+1, 1);
   write(1, &cr, sizeof (cr));



   int pc1 = 0x71;
   putc (pc1, stdout);
   write(1, &cr, sizeof (cr));


/*
   wchar_t wc = 0x4f60;  // U+4F60 '你'

   //printf ("size of wchar_t = %ld, size of int = %ld\n", sizeof( wchar_t ), sizeof ( int )  );
   //printf ("wc = %x\n", wc );

   char *p = setlocale (LC_CTYPE, "");
   //printf ("LC_CTYPE = %s\n", p );

   dprintf (1, "vasya\n");
   putwchar(wc);
   putwchar(0x0A);
*/


return 0;
}


