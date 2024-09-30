#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

void main();




void main() {



    struct sockaddr *  sa1_var;
    struct sockaddr_in *  sa2_var;

    sa2_var = ( struct sockaddr_in * ) sa1_var;



    struct sa3 { 
      int a;
      char b;
      };
      
     struct sa3   sa3_var;
      
      
    struct sa4 { 
      char a;
      long b;
      int c;
      };
 
     struct sa4   sa4_var;
     
     
     
     sa4_var =  (struct sa4 ) sa3_var;
      








}


