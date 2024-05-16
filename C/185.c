
#include <stdio.h>


int main()
{

   

   char cur[]={'2','2','2'};
   for (int i=0; i<sizeof(cur); i++)
   {
       printf("%c", cur[i]);
   }



   sprintf(cur,"%d", 1);
   for (int i=0; i<sizeof(cur); i++)
   {
       printf("%c", cur[i]);
   }

    return 0;
}


