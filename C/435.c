#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#define NUM 8

int main()
{

     char *p_c1 = setlocale(LC_CTYPE,"de_DE.utf-8");
     if (p_c1 == NULL ) {
      printf ("setlocale ERROR \n");
      return (1);
     }


    putwchar(0x0443);
    putwchar('\n');



    return(0);
}



