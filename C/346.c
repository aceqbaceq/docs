#include <unistd.h>
#include <stdio.h>


int main() {

   char vasya[] = "/home/noroot/temp/nc";
   const char *p = vasya;
   if ( chroot (p) < 0 ){
     perror ("chroot error");
   };
   
   


  if (chdir("/dir1") < 0){
      perror ("chdir error");
  }

sleep(60);

return 0;

}

