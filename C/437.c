#include <stdio.h>
#include <wchar.h>
#include <locale.h>


int main() {

     char *p_cl = setlocale(LC_CTYPE,"ru_RU.utf-8");
     if (p_cl == NULL ) {
      printf ("setlocale ERROR \n");
      return (1);
     }



    wchar_t *p = L"у";  // Строка в wchar_t (UTF-32 в Linux, UTF-16 в Windows)

    unsigned char *byte_ptr = (unsigned char *)p; // Приводим к указателю на байты
    size_t size = wcslen(p) * sizeof(wchar_t);   // Считаем размер в байтах (без \0)

    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byte_ptr[i]);  // Выводим каждый байт в 16-ричном виде
    }

    printf("\n");

    char *p_c1 = "\u041f";
    printf("%s\n", p_c1);

    char *p_c2 = "\xD0\xAE";
    printf("%s\n", p_c2);

    char *p_c3 = "\xD0AE";
//    printf("%s\n", p_c3);





/*
    wchar_t *p_w2 = L"\u041f";
    wprintf(L"%ls\n", p_w2);

    wchar_t w3[] = { 0x0000041F, 0x00000000 } ;
    wchar_t *p_w3 = &w3[0];
    wprintf(L"%ls\n", p_w3);

    wchar_t *p_w4 = L"\x0000041F";
    wprintf(L"%ls\n", p_w4);
*/


    return 0;
}


