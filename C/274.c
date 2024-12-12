#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>









int main(int argc, char *argv[])  {





    // проверяю что программы была запущена с 1 аргументом
        if(argc != 2)
    {
    printf("\n Usage: %s </path/to/file> \n",argv[0]);
    return 1;
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }






  pid_t pid_p = getpid();
  printf("PID = %d\n", pid_p);


  int md = -1;
  if (  (md = open(argv[1], O_RDONLY)) < 0 ) {
     perror("error open file = ");
     exit (1);
  }
  
  printf ("md=%i\n", md);
  sleep (30);


   for (int i = 1; i < 100; ++i) {

                 char buffer[4096];
                 int len = read(md, buffer, sizeof(buffer) - 1);
                 if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    //printf("READ DATA FROM STDIN : %s\n", buffer);
                 }


                  sleep(1);

  }




exit (0);
}















