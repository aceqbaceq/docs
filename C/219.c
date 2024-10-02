#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

void main();
void vasya( char argv[] );



void main() {


    char a [] = "kuku";
    vasya ( a ) ;

    
    char * p_P1[4];
    char b[] = "vasya";
    char c[] = "petya";
    char d[] = "kolya";
    p_P1[0] = b;
    p_P1[1] = c;
    p_P1[2] = d;
    p_P1[3] = NULL;

    for (int i=0; p_P1[i] != NULL ; i++) {
        printf (" %i  %s \n", i, p_P1[i]);
    }

}



void vasya( char argv[] ) {


   printf ("%s  \n", argv );

};


