

#include<stdio.h>


void func(){

static int a = 0;
printf( "a=%d\n", a  );
a = a + 1;

};

int main(){

func();
func();
func();



return(0);
};



