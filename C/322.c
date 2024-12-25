#include <stdio.h>
#include <string.h>


int main() {


  //
  char vasya6[10];
  strcpy(vasya6, "9876");
  //printf ("vasya6 = %s \n", vasya6);


  int a  = 10;
  char b = 12;

  //int *p1 = &a;
  //char *p2 = p1;

  int vasya2[10];
  int petya2[10];
//  petya2 = vasya2;

   

  int a2 = 10; // переменная a ее адрес=1234
  int *p [5]; // тело массива начинается с адреса=7689 
  p[0] = &a2;  // в ячейки 7689-7692 будет записан адрес 1234. тоесть p[0]=1234
  int** q = &p[0]; // q=7689
  printf("*q = %p, &a = %p  \n",   *q, &a2  );






}





