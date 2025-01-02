#include <sys/epoll.h>
#include <stdio.h>


int main() {




    printf("uint32_t SIZE = %i \n", sizeof(uint32_t)  );
    printf("epoll_event SIZE = %i \n", sizeof(struct epoll_event)  );


   union vasya {
            void *p;
            int a;
            char b;
   };


    printf("union vasya SIZE = %i \n", sizeof(union vasya)  );

   union vasya u1;
   
   int a = 10;
   u1.p = &a;
   u1.a = 10;
   u1.b = 0x10;




}



