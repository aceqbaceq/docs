#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>

int main(void)
{

char a = 'v';
char b = 'a';
char c = 's';
char d = 'y';
char e = 'a';
printf  ("%c%c%c%c%c\n", a, b, c, d, e);


unsigned char f = 12;
unsigned char g = 0x0a;
printf ("f=%hhu \n", f);
printf ("g=%hhu \n", g);


signed char h = -10;
signed char i = 0xfa;
printf ("h=%hhi \n", h);
printf ("i=%hhi \n", i);





char          a4 = 0xfa;
printf ("a4=%c   \n", a4);
printf ("a4=%hhu \n", a4);
printf ("a4=%hhi \n", a4);





char          a1 = 0xfa;
unsigned char a2 = 0xfa;
signed   char a3 = 0xfa;
printf ("a1=%c   \n", a1);
printf ("a2=%u \n", a2);
printf ("a2=%hhu \n", a2);
printf ("a3=%i \n", a3);



size_t   a5 = 1221314;
printf ("a5=%zu   \n", a5);



ssize_t   a6;
printf ("a6 sizeof =%lu   \n", sizeof(a6));
printf ("a6 sizeof =%zu   \n", sizeof(a6));


ssize_t a7 = -112323123123;
printf ("a7 =%zi   \n", a7);


off_t a8=-121212121212;
printf ("a8  sizeof =%lu   \n", sizeof(a8));
printf ("a8 =%zi   \n", a8);


__intmax_t a9;
printf ("a9  sizeof =%lu   \n", sizeof(a9));


unsigned int a10 = 16384;
printf ("%hhu  \n", a10);


unsigned char a11  = 34;
printf ("a11 = %hhu \n", a11 );
printf ("a11 = %u \n", a11 );


unsigned int  a12  = 257;
printf ("a12 = %hhu \n", a12 );


char a13 = 'r';
printf ("a13 = %c \n", a13 );
printf ("a13 = %hhu \n", a13 );
printf ("a13 = %u \n", a13 );


char  a14  = 0xf9;
printf ("a14 = %c \n", a14 );
printf ("a14 = %hhu \n", a14 );
printf ("a14 = %hhi \n", a14 );


off_t  a15=-44674407370955161 ;
printf ("a15 sizeof = %lu \n", sizeof(a15) );
printf ("a15  = %ji \n", a15 );
printf ("a15  = %ji \n", (intmax_t)a15 );



signed char  a16 = -15;
//printf ("a16  = %ji \n", a16 );
printf ("%ji \n", (intmax_t)a16 );


size_t a17  = 55000;
printf ("%zu \n", a17);

//printf("#define SIZE_MAX %zu\n", (size_t)(-1));


ssize_t a18  = -55000;
printf ("%zi \n", a18);


const char  *a19 = "vasya";
printf ("%s \n", a19);


char  *a20 = "vasya";
printf ("%s \n", a20);



printf ("%hhu \n", (unsigned char)(-1) );


printf ("%ju \n", (intmax_t)(off_t)(-1) );


printf ("%zu \n", (size_t)(-1) );


printf ("%ju \n", (intmax_t)(-1) );



//unsigned octal a21 = 5;
printf ("%o \n", 5 );
printf ("%#o \n", 5 );

unsigned char a23 = 12;
printf ("%o \n", a23 );
printf ("%#o \n", a23 );

unsigned long a24 = 0666;
printf ( "oct view %lo \n",  a24 );
printf ( "dec view %lu \n",  a24 );
printf ( "hex view %lx \n",  a24 );

printf ("---- \n");

printf ( "oct view %#lo \n",  a24 );
printf ( "hex view %#lx \n",  a24 );

printf ("---- \n");


printf ( "oct view|%10lo| \n",  a24 );
printf ( "dec view|%10lu| \n",  a24 );
printf ( "hex view|%10lx| \n",  a24 );

printf ("---- \n");


printf ( "oct view|%010lo| %10s|\n",  a24, "1" );
printf ( "dec view|%010lu| %10s|\n",  a24, "23" );
printf ( "hex view|%010lx| %10s|\n",  a24, "234" );

printf ("---- \n");


signed char a25 = -15;
printf ( "oct view|%10hho| %10s|\n",  a25, "1" );
printf ( "dec view|%10hhi| %10s|\n",  a25, "23" );
printf ( "hex view|%10hhx| %10s|\n",  a25, "234" );

printf ("---- \n");


signed char a26 = 15;
printf ( "view|%-10hhi|\n",  a26 );
printf ( "view|%- 10hhi|\n",  a26 );
printf ( "view|%-+10hhi|\n",  a26 );

printf ("---- \n");


char *old_locale, *saved_locale;

  /* Get the name of the current locale.  */
  old_locale = setlocale (LC_ALL, NULL);

  /* Copy the name so it won't be clobbered by setlocale. */
  saved_locale = strdup (old_locale);
printf ("default locale = %s \n", saved_locale);

setlocale(LC_NUMERIC,"en_US.UTF-8");
signed int a27 = 15000;
signed int a28 = -16000;
signed int a29 = 3845;

printf ( "view|%'-+10i|\n",   a27 );
printf ( "view|%'-+10i|\n",  a28 );
printf ( "view|%'-+10i|\n",  a29 );


printf ("---- \n");
unsigned long a30 = 0x3ab;
printf ( "view|%8lX|\n",  a30 );
printf ( "view|%08lX|\n",  a30 );


printf ("---- \n");
printf ( "%*s \n", 10, "0123456789abc" );

printf ("---- \n");
printf ( "%10.10s \n", "0123456789abc" );
printf ( "%*.10s \n", 10, "0123456789abc" );
printf ( "%*.*s \n", 10, 10, "0123456789abc" );





exit (0);



}





