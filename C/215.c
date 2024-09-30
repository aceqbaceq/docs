#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

void main();




void main() {


   char a[3] = "12";
   printf ("a = %s  \n", a);




     struct s1 {
           int a;
           char name[];
     };


   struct s1 *s = malloc( sizeof(*s) + sizeof(char) * (5 + 1) );
   
   strcpy(s->name, a);
   printf ("name  = %s  \n", s->name );


   char b[3] = "13";
   strcpy(b, s->name);
   printf ("name  = %s  \n", b );



   char c[3] = "56";
   strcpy(s->name, c);
   printf ("name  = %s  \n", s->name );


}

