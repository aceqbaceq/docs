#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

struct myStruct {
    int length;
    char data[3];  // гибкий массив с нулевым размером
};

int main() {
    int data_size = 10;
    
    // Выделяем память для структуры и дополнительной памяти для данных
    struct myStruct *s = malloc(sizeof(struct myStruct) + data_size * sizeof(char));

    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }    

   *(s->data +0 ) = 0x10;
   *(s->data +5 ) = 0x20;
   *(s->data +9 ) = 0x90;
   *(s->data +10 ) = 0x90;
   *(s->data +33*4096 ) = 0x90;


struct myStruct2 {
    int length;
    char data[];  // гибкий массив с нулевым размером
};


  struct myStruct2 s2;
  printf ("s2 адрес = %p \n",  &s2  );

  char (*p)[0] = &(s2.data);
  printf ("char data[] адрес = %p \n",  *p  );

  //*(s2.data) = 0x10;



struct myStruct3 {
    int length;
    char data[0];
};
  

  struct myStruct3 s3;
  printf ("s3 адрес = %p \n",  &s2  );

  char (*p2)[0] = &(s2.data);
  printf ("char data[] адрес = %p \n",  *p  );




//  struct sockaddr {
//           sa_family_t     sa_family;      /* Address family */
//           char            sa_data[];      /* Socket address */
//       };





  struct sockaddr s4;
  struct sockaddr* p4 = &s4;
  sa_family_t* p5 = &(s4.sa_family);
  char (*p6)[14] = &(s4.sa_data);
  printf("полный размер s4 = %i, s4 начальный адрес = %p, sa_data начало = %p   \n",   sizeof(s4),p5,p6 );
//  *(p6+13) = 0x10;

  char arr1[14] = "Hello, world!";
  char (*p9)[14] = &arr1;
  (*p9)[3] = 0x10; // стадартный сопособ доступа к элементу черещ поинтер на массив
  *((*p9)+0) = 0x20;  // более интересный способ
  strcpy(*p9, "abcdefgh");
  printf("%s\n", *p9);
  

  struct struc5 {
    int a;
    char vasya[];
  } s6;
  
  printf ("size s6 = %i \n", sizeof(s6) );
  
  
  struct struc6 {
    char vasya[15];
    int b;
  } ;

  struct struc6  *p24 = malloc (sizeof(struct struc6));
  printf ("struc6 size = %i    \n", sizeof(struct struc6) );


  char pet[0];
  
  struct struc7 {
    char vasya[2];
    int b;
  } ;

  struct struc7 sa6;
  
  printf ("struc7 size = %i    \n", sizeof(sa6) );




};




