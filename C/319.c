#include <stdio.h>

int main() {

   unsigned int a = 10; 
   unsigned int *p = &a;


   long unsigned int *b = (long unsigned int*)p;
   long unsigned int *g = (long unsigned int*)&p;


   printf("Value of mean: *p = %li\n", *p);
   printf("Value of mean: *b = %lli\n", *b);
   printf("Value of mean: *g = %lli\n", *g);
   
 
   char h[10]="123456789";
   char *i = h;
   printf ("адрес h = %p, адрес i = %p, контент h = %s, контент i = %s", &h, i, h, i);

}




