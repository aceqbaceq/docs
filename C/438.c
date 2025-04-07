#include <stdio.h>
#include <wchar.h>


int main() {
    wchar_t *p = L"�";  // ������ � wchar_t (UTF-32 � Linux, UTF-16 � Windows)

    unsigned char *byte_ptr = (unsigned char *)p; // �������� � ��������� �� �����
    size_t size = wcslen(p) * sizeof(wchar_t);   // ������� ������ � ������ (��� \0)

    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byte_ptr[i]);  // ������� ������ ���� � 16-������ ����
    }

    printf("\n");
    return 0;
}

