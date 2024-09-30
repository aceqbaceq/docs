#include <stdio.h>

// decalire struct type
struct car {
    char *name;
    float price;
    int speed;
};



// declaire list of all functinions
void main();
void set_price(struct car *p_C1);



// specify main() body
void main () {

struct car lada01;

lada01.name = "kalina";
lada01.price=2.3;
lada01.speed = 100;

printf ("price = %f \n", lada01.price );
printf ("=====================\n\n");



struct car *p_P1 = &lada01;

set_price( p_P1);

}



void set_price(struct car *p_C1) {

  p_C1->price = 5.6;
  printf ("price = %f \n", p_C1->price );


};




