#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};




void main () {


struct car lada01;

lada01.name = "kalina";
lada01.price=2.3;
lada01.speed = 100;

int vasya = lada01.speed;

printf ("name  = %s \n", lada01.name );
printf ("price = %f \n", lada01.price );
printf ("speed = %i \n", lada01.speed);
printf ("=====================\n\n");




struct car *p_p1;
p_p1=&lada01;
printf ("speed=%i \n", p_p1->speed );
printf ("=====================\n\n");




  int *p_p3;
  int petya = 5;
  p_p3 = &petya;
  int kuku = *p_p3;
  printf ("kuku = %i \n", kuku );
  printf ("*p_p3 = %i \n", *p_p3 );
  printf ("=====================\n\n");
  
  void *p_p4;
  p_p4 = &petya;
  int *p_p5 = p_p4;
  int kolya = *p_p5;
  printf ("*p_p5 = %i \n", *p_p5 );
  printf ("=====================\n\n");


  printf ("*p_p4 = %i \n", *(int *) p_p4 );
  printf ("=====================\n\n");



}






