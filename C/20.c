#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{

    pid_t child_pid = fork();
    if (child_pid == 0){
        printf("child: i am inside the child, waiting for 10 sec in the child\n"); 
        sleep(10);}
    else
    {
        printf("parent: i am inside the parent. i am waiting and doing nothing until the child  exits to continue\n");
        wait(NULL);
        printf("parent: i am continuing inside the parent because child has terminated\n");
    }


    if (child_pid == 0){
        printf("child:child is saying GoodBye!\n");}
    else
      {
         printf("parent:parent is saying GoodBye!\n");
      }
    return 0;

}
