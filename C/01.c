#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int sig_num)
{
if(sig_num == SIGINT)
{
printf("\n Vasya! ты послал вменя сигнал siginit!Caught the SIGINT signal\n");
}
else
{
printf("\n Caught the signal number [%d]\n", sig_num);
}

// Do all the necessary clean-up work here

//exit(sig_num);
}

int main(void)
{
//Register signal handler through the signal() function
signal(SIGINT, sig_handler);

while(1)
{
//simulate a delay -- as if the program is doing some other stuff
sleep(1);
}

return 0;
}
