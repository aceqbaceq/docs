#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>

int main(void)
{


int a;
a = 1;

int *b;
int c;
c = 1;
b = &c;






//

int a1;
a1 = 10;

int b1;
b1 = 20;

//а теперь обьявлю поинтер

int * Ptr_c1;
Ptr_c1 = &a1;


//
int * ptr_C2;
int c2;
c2 = 10;
ptr_C2 = &c2;
int c3;
c3 = 20;
ptr_C2 = &c3;
c3 = 30;



//
int const * ptr_D2;
const int d2 = 10;
ptr_D2 = &d2;
int d3 = 30;
ptr_D2 = &d3;
d3 = 40;






//
const int EE1 = 10;



//
int e3 = 40;
int * const  ptr_E3 = &e3 ;
e3 = 50;
int e4 = 50;

//
const int f1 = 10;
int const * const ptr = &f1;

//
int f2;
f2 = 20;
int const * const F = &f2;
f2 = 30;


//
unsigned int g1 = -20;
printf ("==========================\n");
printf ( "%hu \n" ,g1);

//
unsigned short int h1;
h1 = 10;
unsigned short int * ptr_H1;
ptr_H1 = &h1;
printf ("==========================\n");
printf ( "H1 = %hu \n"   ,*ptr_H1);



//
unsigned char h3;
h3 = 'a';
printf ("==========================\n");
printf ( "h3 = %hhu \n",  h3);



//
unsigned short int i[2];
i[0] = 1;
i[1] = 2;

printf ("==========================\n");
printf ( "i[0] = %hu \n"   , i[0]    );



//
int j[ 2 ] = { 2, 3 };

//
char k[4];
k[0] = -1;
k[1] = 02;
k[2] = 0x7;
k[3] = 'a';
printf ( "k[0] = %hhi \n"   , k[0]    );
printf ( "k[1] = %#hho \n"   , k[1]    );
printf ( "k[2] = %hhX \n"   , k[2]    );
printf ( "k[3] = %hhu \n"   , k[3]    );
printf ("==========================\n");


//
char n[ 4 ] =  { -1, 02, 0x7, 'a'    };
printf ( "n[0] = %hhi \n"   , n[0]    );
printf ( "n[1] = %#hho \n"   ,n[1]    );
printf ( "n[2] = %hhX \n"   , n[2]    );
printf ( "n[3] = %hhu \n"   , n[3]    );
printf ("==========================\n");






//
unsigned char p[ 5 ] =  { 'v', 'a', 's', 'y', 'a'    };
for (   unsigned char t1=0;     t1<(  sizeof(p) / sizeof(p[0])  );      t1++) {
   printf ( "p[%hhu] = %hhX \n"   , t1,p[t1] );
}

for (   unsigned char t1=0;     t1<(  sizeof(p) / sizeof(p[0])  );      t1++) {
   printf ( "p[%hhu] = %c \n"   , t1,p[t1] );
}

for (   unsigned char t1=0;     t1<(  sizeof(p) / sizeof(p[0])  );      t1++) {
   printf ( "%c"   , p[t1] );
}
printf ( "\n" );
printf ("==========================\n");




//
char q[ 6 ] =  "petya";
for (   unsigned char t1=0;     t1<(  sizeof(q) / sizeof(q[0])  );      t1++) {
   printf ( "q[%hhu] = %c \n"   , t1,q[t1] );
}
for (   unsigned char t1=0;     t1<(  sizeof(q) / sizeof(q[0])  );      t1++) {
   printf ( "%c"   , q[t1] );
}
printf ( "\n" );
printf ("==========================\n");




//
q[0] = 'm';
for (   unsigned char t1=0;     t1<(  sizeof(q) / sizeof(q[0])  );      t1++) {
   printf ( "%c"   , q[t1] );
}
printf ( "\n" );
printf ("==========================\n");




//
unsigned short int r = 'k';
   printf ( "%c \n"   , (char) r );
printf ("==========================\n");






//

unsigned short int s[ 5 ] = { 'b', 'o', 'r', 'o', 'v' }; 
for (   unsigned char t1=0;     t1<(  sizeof(s) / sizeof(s[0])  );      t1++) 
   printf ( "%c"   , s[t1] );
printf ( "\n" );
printf ("==========================\n");



//
int d34[] = {1,2,3};
int * prt_d43 = d34;




//
unsigned char u[ 6 ] = { 'v', 'o', 'r', 'o', 'n', 0x0 }; 
char const * ptr_u = u;
printf ("%s\n", ptr_u);
printf ("==========================\n");



//
unsigned short int r3[ 6 ] =  { 'k', 'o', 'l', 'y', 'a', 0x00 } ;

//
signed char s2 = 'a';


//
char const v[ 6 ] = { 'v', 'o', 'r', 'o', 'n', 0x0 }; 
char const * ptr_v = v;
printf ("%s\n", ptr_v);
printf ("==========================\n");


//
char const w[ 6 ] = "voron";
char const * ptr_w = w;
printf ("%s\n", ptr_w);
printf ("==========================\n");


//
char const * ptr_w2 = "voron";
printf ("%s\n", ptr_w2);
printf ("==========================\n");


//
char w3[] = "ventilyator";



//
char * ptr_w4 = "toron";
printf ("%s\n", ptr_w4);
printf ("==========================\n");


//
char const * ptr_w5 = "toron2";
printf ("%s\n", ptr_w5);
printf ("==========================\n");



//
int a20 = 1;
int a21 = 2;
int a22 = 3;
int * ptr_a20a [ 3 ] = { &a20, &a21, &a22 };

for (   unsigned char t1=0;     t1<(  sizeof(ptr_a20a) / sizeof(ptr_a20a[0])  );      t1++) {
   printf ( "ptr_a20a[%hhu] = %i\n"   , t1, *ptr_a20a[t1] );
}
printf ("==========================\n");



//
char const bb1[] = "mama";
char const bb2[] = "mila";
char const bb3[] = "ramu";
char const  * ptr_bb [ 3 ] = { bb1, bb2, bb3 };

for (   unsigned char t1=0;     t1<(  sizeof(ptr_bb) / sizeof(ptr_bb[0])  );      t1++) {
   printf ( "ptr_bb[%hhu] = %s\n"   , t1, ptr_bb[t1] );
}
printf ("==========================\n");



//
char const  * ptr_bc [ 3 ] = { "klara", "u" , "karla" };

for (   unsigned char t1=0;     t1<(  sizeof(ptr_bc) / sizeof(ptr_bc[0])  );      t1++) {
   printf ( "ptr_bc[%hhu] = %s\n"   , t1, ptr_bc[t1] );
}
printf ("==========================\n");



//
char const * ptr_w6[] = { "alpha", "bravo", "charlie", "zero" };















exit (0);



}





