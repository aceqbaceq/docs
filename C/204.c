#include <stdio.h>

// declaire list of functins 
void func1 (int B);
void main();


// specify main body
void main() {
    
int A = 1;

func1(A);

 printf ("A=%i \n", A);


}


// specify func1 body
void func1 (int B){
    
 printf ("B=%i \n", B);

 B=10;

 printf ("B=%i \n", B);

}


