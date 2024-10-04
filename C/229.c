
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>




int main(void)
{


        short int i1;
        printf ( " short int = %i (size in bytes) \n", sizeof(i1) );
        printf ( "========================================\n\n" );


        int i2;
        printf ( " int = %i (size in bytes) \n", sizeof(i2) );
        printf ( "========================================\n\n" );


        long int i3;
        printf ( " long int = %i (size in bytes)  \n", sizeof(i3) );
        printf ( "========================================\n\n" );



        struct sockaddr_storage s1;
        printf ( " struct sockaddr_storage = %i (size in bytes) \n", sizeof(s1) );
        printf ( "========================================\n\n" );


        struct sockaddr s2 ;
        printf (" struct sockaddr {\n");
        printf ("        sa_family_t     sa_family;      /* Address family */ \n");
        printf ("        char            sa_data[];      /* Socket address */ \n");
        printf (" };\n\n");

        printf ( " struct sockaddr = %i (size in bytes) \n", sizeof(s2) );
        printf ( " sa_family = %i (size in bytes) \n", sizeof(s2.sa_family) );
        printf ( " sa_data[] = %i (size in bytes) \n", sizeof(s2.sa_data) );
        printf ( "========================================\n\n" );



       


}


