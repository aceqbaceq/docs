#include <stdio.h>
#include <unistd.h>

int main() {

	int pid = getpid();
	printf ("pid = %d\n",pid);

	          char buffer[256];
                 int len = read(1, buffer, sizeof(buffer) - 1);
                 if (len > 0) {
                    buffer[len] = '\0';  // Null-terminate the string
                    printf("PARENT PROCESS. READ DATA FROM /dev/ptmx : %s", buffer);
                 }



    return 0;
}
