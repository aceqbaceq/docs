#include <unistd.h>
#include <stdio.h>




int main()
{

    unsigned char f=0x0;
    ssize_t  r;
    char buf[5] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
    void * ptr_buf = &buf;
        for (int t=0; t<5; t++){
            f = *((unsigned char *)(buf+t));
	    printf ("buf = %#x\n", (unsigned int) f   );
        }
            printf ("=====\n");


        r = read(0, ptr_buf, 5);
        printf ("\nsize r = %i\n",(int) r);

        for (int t=0; t<5; t++){
            f = *((unsigned char *)(buf+t));
	    printf ("buf = %#x\n", (unsigned int) f   );
        }
            printf ("=====\n");



    return 0;
}



