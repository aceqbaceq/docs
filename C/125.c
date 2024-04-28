#include <stdio.h>
#include<math.h>



int main(void) {

    /*
    int i, j;
    printf ("введи два числа через пробел: ");
    scanf ("%i%i", &i, &j);
    printf ("ты ввел числа: %i %i \n", i, j );

    if ( i > j  ) {
	printf ("%i > %i \n", i, j);
    }
    else {
	printf ("%i < %i \n", i, j);
    }
    */
	

/*
    int k = 1;
    while (k < 10) {
	printf ("k=%i\n", k);
	k = k + 1;
    }
*/


/*
    int i,j;
    i=10;
    j=3;
    int k = i / j;
    printf ("i=%i, j=%i, k=%i\n",    i, j, k);
*/



/*
    int i,j;
    i=10;
    j=3;
    float l;
    l = i / (float j );
    printf ("i=%i, j=%i, l=%f \n",    i, j, l);


    int m = 1;
    int (*iPtr);
    iPtr = (&m);
*/


/*
    int n=1;
    float temp,temp2,e;
    while ( n < 100  ) {
	temp = (1+1/(float)n);
	temp2 = pow( temp, n );
	e = e + temp2;
        printf ("temp=%f, temp2=%f, e=%f\n", temp, temp2, e);
	n = n + 1;
    }

    printf ("e=%f\n", e);
*/



/*
    int i = 1;
    printf ("%i\n", i++);
    printf ("%i\n", i);
    printf ("%i\n", ++i);
    printf ("%i\n", i);
*/



/*
    int i = 0;
    while (i++ < 10) {
	printf ("%i ",i);
    }
    printf ("\n");
*/


/*
    for ( int a=1; a < 10; a++ ) {
	printf ("%i ",a);

    }
*/





    char a;

    while ( ( a = getchar() ) != EOF ) {
	printf ("%c", a); 
    }





/*
    char a;


    while ( ( a = getchar() ) != EOF ) {
	if ( a != 0x0a ) {
	printf ("вы ввели = %c \n", a); 
	}
    }


    if ( a = 0x0a ) {
	printf ("вы нажали Ctrl+D что аналогично вы нажали EOF, заканчиваю работу. пока.");
    }

*/




/*    printf ("\n"); */
    return(0);
};






