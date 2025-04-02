#include <stdio.h>
#include <locale.h>

int main()
{
    char *locale;

    locale = setlocale(LC_ALL,0x00);
    printf("The current locale is %s\n",locale);

    return(0);
}

