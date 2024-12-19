#define _POSIX_C_SOURCE  200809L
#include <sys/socket.h>
#include <stdio.h>


int main() {

    //
    struct sockaddr s1;
    dprintf (1, "sockaddr SIZE = %hi \n", sizeof(s1) );
    dprintf (1, "sockaddr  sa_family SIZE = %hi \n", sizeof(s1.sa_family) );
    dprintf (1, "sockaddr  sa_data[] SIZE = %hi \n",  sizeof(s1.sa_data) );



    //
    sa_family_t  a1;
    dprintf (1, "sa_family_t SIZE = %hi \n", sizeof(a1) );

    //
    char vasya[10];
    dprintf (1, "char vasya[10] SIZE = %hi \n", sizeof(vasya) );

    //
    unsigned char kuku[10]={ [0 ... 9] = 0xAA };
    printf("\n");
    for (unsigned short int i=0; i<sizeof(kuku); i++) {
	dprintf (1, "kuku[%hhi] = %hhX\n", i, kuku[i] );
    }
    
    //
    char petya[10] = "123456789";
    dprintf (1, "char petya[10] = %s \n", petya );

    //
    char kolya[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 0x00};
    dprintf (1, "char kolya[10] = %s \n", kolya );
    
    //
    kolya[0] = 'a';
    kolya[1] = 'A';
    kolya[2] = 'b';
    kolya[3] = 'B';
    kolya[4] = 'c';
    kolya[5] = 'C';
    kolya[6] = 'd';
    kolya[7] = 'D';
    kolya[8] = 'e';
    kolya[9] = 0x00;
    dprintf (1, "char kolya[10] = %s \n", kolya );


    //
    dprintf (1, "\n");
    for (unsigned short int i=0; i<sizeof(kolya); i++) {
	dprintf (1, "kolya[%hi] = %x\n", i, kolya[i] );
    }



   //
   unsigned int b2[10]={1, 2, 3, 4, 5, 6, 7, 8, 9};
   dprintf (1, "\n"
	"b2[10] SIZE = %hhi \n"
	"адрес первого элемента в памяти = %p \n"
        "b2[0] = %hhX \n"
                , sizeof(b2), b2, b2[0] );
    dprintf (1,"b2[0] SIZE = %hi\n", sizeof(b2[0]) );


    //
    struct sockaddr s2;
    s2.sa_family   = 0xAAFF;
    s2.sa_data[0]  = 0x01;
    s2.sa_data[1]  = 0x02;
    s2.sa_data[2]  = 0x03;
    s2.sa_data[3]  = 0x04;
    s2.sa_data[4]  = 0x05;
    s2.sa_data[5]  = 0x06;
    s2.sa_data[6]  = 0x07;
    s2.sa_data[7]  = 0x08;
    s2.sa_data[8]  = 0x09;
    s2.sa_data[9]  = 0xAA;
    s2.sa_data[10] = 0xBB;
    s2.sa_data[11] = 0xCC;
    s2.sa_data[12] = 0xDD;
    s2.sa_data[13] = 0xEE;
    
    

    dprintf (1, "s2.sa_family = %hX \n", s2.sa_family );
    for (unsigned short int i=0; i<sizeof(s2.sa_data); i++) {
	dprintf (1, "s2.sa_data[%hi] = %hhX\n", i, s2.sa_data[i] );
    }


    char ch1[10];
    printf("%i\n", sizeof(ch1) );
    
    
    
   int a = 0xAABBCCDD;
   int *p1 = &a;
   char *p2 = (char *)p1;
   printf("%hhX \n", *p2);


}





