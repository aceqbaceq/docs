#include <stdio.h>


int f1 ( int (*bPtr)( void ) );
int f2 ( void );
int f3 ( void );



int main(void) {

    int (*aPtr) (void );

    aPtr = &f2;
    f1( aPtr );

    aPtr = &f3;
    f1( aPtr );



    return(0);
};



int f1 ( int (*bPtr)( void ) ) {
    (*bPtr) ();

};


int f2 ( void ) {
    printf ( "привет изнутри функции f2 \n"     );

};


int f3 ( void ) {
    printf ( "привет изнутри функции f3 \n"     );

};









