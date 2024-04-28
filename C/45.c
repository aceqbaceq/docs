#include <stdio.h>
#include <stdlib.h>

void vasya (int x, int *z){

// increase and print var x
    x++;
    printf("func: x=%d\n", x);

    //increase and print *z
    (*z)++;
    (*z)++;
    printf("func vasya: *z=%d\n", *z);


};

int main(){

// определяем переменные

  int a;
  void *a_Ptr;
  a = 1;
  a_Ptr = &a;
// печааем здест фишка в том что поинтер типа void хрен напечатаешь без преобразования его во чтото. 
// в данном случае в int
  printf("main: a=%d, *a_Ptr=%d\n",  a,  *(int*)a_Ptr  );



  int *b_Ptr;
 *b_Ptr = 2;
// печатаем
  printf("main: b_Ptr=%d\n",  *b_Ptr  );



// вызывем фукнкцию которая меняет переменные. одну переменную передавем через копирование а вторую через поинтер.
  vasya(a, b_Ptr);

// печатаем все переменые еще раз смотрим изменилиь ли они после функции
   puts("main: print variables after function call:");
   printf("main: a=%d, *a_Ptr=%d\n",  a,  *(int*)a_Ptr  );
   printf("main: b_Ptr=%d\n",  *b_Ptr  );


return(0);
};



