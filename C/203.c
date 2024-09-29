#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};




void set_price(struct car *c, float new_price);



void main () {

struct car lada01;

lada01.name = "kalina";
lada01.price=2.3;
lada01.speed = 100;

printf ("name  = %s \n", lada01.name );
printf ("name  = %s \n", lada01.name );
printf ("price = %f \n", lada01.price );
printf ("speed = %i \n", lada01.speed);
printf ("=====================\n\n");



struct car *p_p1 = &lada01;

printf ("price = %f \n", p_p1->price );
printf ("=====================\n\n");


set_price( p_p1, 500);
printf ("new price = %f \n", lada01.price );
printf ("=====================\n\n");



}



void set_price(struct car *c, float new_price) {

  c->price= new_price;

};



