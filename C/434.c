#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#define NUM 8

int main()
{
    wchar_t hello[NUM] = {
        0x41f, 0x440, 0x438, 0x432, 0x435, 0x442, 0x021
    };
    int x;

//    setlocale(LC_CTYPE,"en_US.UTF-8");
     char *p_c1 = setlocale(LC_CTYPE,"C2.iso88598");
     if (p_c1 == NULL ) {
      printf ("setlocale ERROR \n");
      return (1);
     }
     
    
/*
    for(x=0;x<NUM;x++)
        putwchar(hello[x]);
    putwchar('\n');
*/

    putwchar(0x2016);
    putwchar('\n');

    putwchar(0x00BE);
    putwchar('\n');

    putwchar(0x2018);
    putwchar('\n');



    return(0);
}



