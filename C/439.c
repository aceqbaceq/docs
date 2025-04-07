#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>


int main() {

     char *p_cl = setlocale(LC_CTYPE,"ru_RU.utf-8");
     if (p_cl == NULL ) {
      printf ("setlocale ERROR \n");
      return (1);
     }

/*
    putc(0x71, stdout);
    putc('\n', stdout);


    putc(0xD0, stdout);
    putc(0xAE, stdout);
    putc('\n', stdout);


    putwchar(0x041f);
    putwchar('\n');

*/

/*
    char cc = 0x71;
    write(1, &cc, sizeof(cc));
    cc = 0x0A;
    write(1, &cc, sizeof(cc));

 
    putc(0x71, stdout);
    putc(0x0A, stdout);


    long int i1 = 0x0A77767574737271;
    write(1, &i1, sizeof(i1));



    char c1[] = { 0xd0,  0xae,  0x0A };
    char *buf = &c1[0];
    write(1, buf, sizeof(c1));
*/


    short int i2[] = { 0xAED0,  0x7271,  0x000A };
    short int  *buf = &i2[0];
    write(1, buf, sizeof(i2));

/*
    char c2[] = { 'a',  'b',  0x0A };
    buf = &c2[0];
    write(1, buf, sizeof(c2));

    //char *c3 = "\u041f\x0A";
    //char *c3 = "\u041f\u000A";
    char *c3 = "\u041f\x0A";
    write(1, c3, strlen(c3));

     for(char i = 0; i <= strlen(c3); ++i) {
      printf("%02hhX\n", c3[i]);
    }


*/

    return 0;
}


