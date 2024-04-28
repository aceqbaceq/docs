#include <stdio.h>
#include <stdlib.h>



int main(void)
{

unsigned char a = 255;
signed char   b = -100;


printf ("a = %hhu \n", a);
printf ("b = %hhi \n", b);

printf ("a=%c, b=%hhx \n", a, b);
printf ("b=%hhi \n", b);


unsigned short d = 767;
printf ("d=%hhu  \n", d);


char var1 = 'E';
printf ("var1=%hhu  \n", var1);


char ch1;
ssize_t  s1;
printf ("char=%lu, ssize_t=%zu \n", sizeof(ch1), sizeof (s1));


off_t v2=-111;
printf ("size off_t=%lu, off_t=%li \n", sizeof(v2), v2);




exit (0);

}





