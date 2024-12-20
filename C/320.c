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


   //
    char ch1[10];
    printf("%i\n", sizeof(ch1) );
    
    
   //    
   int a = 0xAABBCCDD;
   int *p1 = &a;
   char *p2 = (char *)p1;
   printf("%hhX \n", *p2);

   //
   char s3[]  = "1234";
   char *p  = s3;
   dprintf (1, "*p = %s \n", p );


   //
   long int vas1;
   long long int vas2;
   printf ("long int SIZE = %i, long long int SIZE = %i \n", sizeof(vas1), sizeof(vas2) );
   int i4[2]={ 0x11111111, 0x22222222 };
   int *p5 = i4;
   int i5 = *p5;
   printf ("*i5= %X \n", i5 );
   long int i6 = *p5;
   printf ("*i6= %lX \n", i6 );
   long int *p6 = (long int *)i4;
   long int i7 = *p6;
   printf ("*i7= %lX \n", i7 );


   //
   unsigned  int  i2 = 0x004E4E4E;
   char *p3 = (char *)&i2;
   dprintf (1, "*p3 = %s \n", p3 );

   //
   unsigned  int  i3 = 0x4D4E4E4E;
   char *p4 = (char *)&i3;
   printf ("%c \n" , p4);

   //
   char neptun[2] = { 0x10, 0x12 };
   char *p_p1 = neptun;
   char *p_p2 = &neptun[0];
   char *p_p3 = &neptun[1];
   printf ("p_p1 = %p, p_p2 = %p, p_p3 = %p\n", p_p1, p_p2, p_p3);
   printf ("*p_p1 = %hX, *p_p2 = %hX *p_p3 = %hX \n", *p_p1, *p_p2, *p_p3);
   
   //
   int ii_1[3] = { 0xAABBCCDD, 0xEEEEEEE, 0XFFFFFFFF};
   int *p_ii = &ii_1[1];
   *p_ii = 0xBBBBAAAA;
   printf ("ii_1[1] = %X \n", ii_1[1] );
   printf ("ii_1[0] = %X, ii_1[1] = %X, ii_1[2] = %X,\n", ii_1[0], ii_1[1], ii_1[2] );
   
   //
   int a43 = 0x1111110A;
   char *p43 = (char *)&a43;
   printf ("*p32 = %hhX \n", *p43 );


}





