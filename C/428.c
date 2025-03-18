#include <stdio.h>


int main() {

     int i3 = 0x00737271;
     char c3[5] = { 0x71, 0x72, 0x73, 0x00  };

     printf ("i3 = %s\n", &i3 );
     printf ("c3 = %s\n", &c3);

return 0;

}

