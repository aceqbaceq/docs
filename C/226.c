#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/prctl.h>  /* Definition of PR_* constants */
#include <sys/prctl.h>


void main();




void main() {


    int s;
    s = prctl(PR_SET_NAME,"Ehal Greka Cherez Reku\0",NULL,NULL,NULL); // name: myProcess
    if ( s == -1 ) {
      printf ("error! \n");
    }

    int prctl(int op, ...);



    sleep (120);





}



