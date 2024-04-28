#include <stdio.h>
#include <stdlib.h>


int main(){

  int ma;
  void *b_Ptr;
  int *c_Ptr;
  int *d_Ptr;

  ma = 1;
  b_Ptr = &ma;
  c_Ptr = &ma;
  d_Ptr = &ma;


  printf("ma=%d, mc=%d, mb=%d\n",  ma,  *c_Ptr, *(int*)b_Ptr );

  (*d_Ptr)++;

  printf("ma=%d, *d_Ptr=%d\n",  ma,  *d_Ptr );


return(0);
};
