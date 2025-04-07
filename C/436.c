#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#define NUM 8

int main()
{

     char *p_c1 = setlocale(LC_CTYPE,"ru_RU.utf-8");
     if (p_c1 == NULL ) {
      printf ("setlocale ERROR \n");
      return (1);
     }


    char* str = "Вася\n";
//    printf("%s\n", str);  

    char *p_c = "\x71\x72\x73\x00";
//    printf("%s\n", p_c);


    wchar_t *wstr = L"\x090D\x041F";
    wprintf(L"String: %ls\n", wstr);


    return(0);
}



