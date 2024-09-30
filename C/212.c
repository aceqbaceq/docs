#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

void main();




void main() {


    struct st1 {
      int  a;
      char b;
    };
    

    struct st1 vasya;
    struct st1 *p_P1 = &vasya;
    
    
    vasya.a=10;
    vasya.b = 'a';
    
    printf ( "vasya.a = %i  \n", vasya.a );
    
    
    
    int i1 = p_P1->a;
    printf ( "i1 = %i  \n", i1 );




}


