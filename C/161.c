#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>



int main(int argc, char *argv[])
{



        pid_t pid = 0;


if (argc != 2){
      printf ("you have not put cmd line argument for pid ==> using pid=getpid() instead\n");
      pid = getpid();
      }

else 
    pid = atoi(argv[1]);

printf("pid = %i\n", pid);





int rc = 0;
cpu_set_t  mask ;
cpu_set_t * ptr_mask = &mask;

int cpun = CPU_COUNT(ptr_mask);
printf ("CPU_COUNT = %i\n", cpun);

rc =  sched_getaffinity(pid, sizeof(cpu_set_t), &mask);
if ( rc != 0 ){
   printf ("ERROR: sched_getaffinity returned Fail\n");
   exit(1);
}






int cc = 0;
for (int t=0; t<cpun; t++) {
  cc =  CPU_ISSET_S(t, sizeof(cpu_set_t), ptr_mask);
  if (cc != 0 )
     printf ("t=%i, cc=%i\n", t, cc);
}


exit(0);

}




