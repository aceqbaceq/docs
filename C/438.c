#include <stdio.h>
#include <wchar.h>


int main() {
    wchar_t *p = L"у";  // Строка в wchar_t (UTF-32 в Linux, UTF-16 в Windows)

    unsigned char *byte_ptr = (unsigned char *)p; // Приводим к указателю на байты
    size_t size = wcslen(p) * sizeof(wchar_t);   // Считаем размер в байтах (без \0)

    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byte_ptr[i]);  // Выводим каждый байт в 16-ричном виде
    }

    printf("\n");
    return 0;
}

