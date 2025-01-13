#include <stdio.h>


int main() {

    char a = 0x10;
    char *p = &a;
    char **b = &p;
    printf("a = 0x%hhX,  a+1 = 0x%hhX  \n",      a, a+1     );
    printf("p = %p,  p+1 = %p  \n",      p, p+1     );
    printf("*p = 0x%hhX,  *p+1 = 0x%hhX  \n",      *p, *p+1    );
    printf("b = %p,  b+1 = %p  \n",      b, b+1     );
    printf("*b = %p,  *b+1 = %p  \n",      *b, *b+1     );
    printf("**b = 0x%hhX,  **b+1 = 0x%hhX  \n",      **b, **b+1     );


    printf("\n");
    a = 0x10;
    printf("a = 0x%hhX  \n",    a);
    printf("a++ = 0x%hhX  \n",    a++ );

    a = 0x10;
    printf("a = 0x%hhX, a++ = 0x%hhX  \n",    a, a++ );



    printf("\n");
    a = 0x10;
    printf("a = 0x%hhX  \n",    a);
    printf("++a = 0x%hhX  \n",    ++a );

    a = 0x10;
    printf("a = 0x%hhX, ++a = 0x%hhX  \n",    a, ++a );


    printf("\n");
    a = 0x10;
    char q = 0x20;
    q = q + a++;
    printf("q = 0x%hhX \n", q);


    printf("\n");
    a = 0x10;
    q = 0x20;
    q = q +   ++a;
    printf("q = 0x%hhX \n", q);




return 0;
}


