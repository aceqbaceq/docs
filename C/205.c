#include <stdio.h>

// declaire list of functins 
void func1 (int *p_B);
void main();


// specify main body
void main() {

  int A = 1;
  int *p_p1 = &A;

  func1(p_p1);

 printf ("A=%i \n", A);


}


// specify func1 body
void func1 (int *p_B){
    
 printf ("*p_B=%i \n", *p_B);

 *p_B=10;

 printf ("*p_B=%i \n", *p_B);

}



