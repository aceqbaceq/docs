#include <stddef.h>




    int func1( char * arr[]){
      return 0;
    };



int main() {


    char a  = 0x10;
    char *mas[2] = { &a, NULL };
    char **p1 = &(mas[0]);
    func1(p1);


return 0;

};
