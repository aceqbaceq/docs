#include <stdio.h>
#include <unistd.h>
 
  int main()
  {
     FILE *fp = fopen("rfile.txt", "w+");
     fprintf(fp+1, "Invalid Write\n");
     fclose(fp);
     return 0;
 }

