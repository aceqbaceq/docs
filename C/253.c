#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>






int main()
{

  pid_t pid_p = getpid();
  printf("parent PID = %d\n", pid_p);


// открывваю и активирую терминал
  int md = -1;
  md = open("/dev/ptmx", O_RDWR | O_NOCTTY);

  int sl1 = -1;
  sl1 = grantpt(md);
  sl1 = unlockpt(md);


// узнаю номер pts/N
  char * ptr_sln = NULL;
  ptr_sln = ptsname(md);
  printf ("pts name = %s\n", ptr_sln);



// читаю из ptmx
  char buffer[256];
  int len = read(md, buffer, sizeof(buffer) - 1);
     if (len > 0) {
            buffer[len] = '\0';  // Null-terminate the string
            printf("READ DATA FROM /dev/ptmx : %s", buffer);
     }



  close (md);



exit (0);


}













