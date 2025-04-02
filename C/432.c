#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main()
{
    wchar_t suits[4] = {
        0x2660, 0x2665, 0x2663, 0x2666
    };
    wchar_t s;
    int x;

    setlocale(LC_CTYPE,"UTF-8");

    printf("Enter suit: ( ");
    for(x=0;x<4;x++)
    {
        wprintf(L"%lc ",suits[x]);
    }
    printf("): ");

    wscanf(L"%lc",&s);
    wprintf(L"Suit set to %lc\n",s);

    return(0);
}


