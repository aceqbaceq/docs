#include <stdio.h>
#include <wchar.h>


int main () {

/*
   int c = 0x00000071;
   int CR = 0x0000000A;
   putc(c, stdout);
   putc(CR, stdout);

   int u1 = 0x000000D0;
   int u2 = 0x000000AE;
   putc(u1, stdout);
   putc(u2, stdout);
   putc(CR, stdout);
*/

  // printf("wchar_t SIZE = %d\n", sizeof(wchar_t));
  // wchar_t wc = 0x1F600;
  // putwchar(L'Ю' );
   wprintf(L"Registered Trade Mark: %ls\n", L"®®");

   return 0;
}


