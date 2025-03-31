# include <unistd.h>
# include <stdio.h>
# define FD_NAME 0


int main() {
   int rp = isatty( FD_NAME  );
   if ( rp == 1 ){
      printf("процесс подключен к терминалу!\n");
      printf("имя файла терминала = %s\n", ttyname(FD_NAME) );

   }

return 0;

}




