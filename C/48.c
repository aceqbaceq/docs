#include <unistd.h> 
#include <sys/types.h>

int main(){
pid_t pid_1;
pid_1 = setsid();
sleep (180);

return (0);
};
