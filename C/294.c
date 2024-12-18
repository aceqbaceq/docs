#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(void) {
 
    /* we can use void*'s to store the program break */
    void *proc_break = sbrk(0);
   
    printf("Boundary: %p\n", proc_break);
   
    /* should increase by 4 bytes */
    if (brk(proc_break + 4) < 0) {
        perror("Couldn't Allocate Memory!!!\n");
        exit(1);
    }
   
    /* observe the wonderful black magic of pointer type-casting! */
    int *int_ptr = (int*)proc_break;
    *int_ptr = 16;
   
    printf("This is stored at %p : %i\n", int_ptr, *int_ptr ); 
    printf("Boundary: %p\n", sbrk(0));
 
    float *f_ptr = (float*)proc_break;
    *f_ptr = 0.1;
    printf("And now %p holds a float %.30f\n", f_ptr, *f_ptr);
   
    printf("Now I'm \"freeing\" that memory...\nsbrk(0) returns %p\n", sbrk(0));
    if (brk(proc_break) < 0) {
        perror("Couldn't Deallocate!!!\n");
        exit(2);
    }
 
    printf("But now it returns... %p\n", sbrk(0));
    printf("Now let's allocate for 'hello world'\n");
 
    char *feed = "hello world"; // we're gonna copy this literal to the heap!
 
    if (brk(proc_break + strlen(feed)+1 ) < 0) {
        perror("Couldn't Allocate Memory!!!\n");
        exit(3);
    }
 
    char *c_ptr = (char*)proc_break;
   
    for (int i = 0; i < strlen(feed) + 1; i++)
        c_ptr[i] = feed[i];
 
    printf("c_ptr = %p and holds %s\n", c_ptr, c_ptr);
 
    brk(proc_break - 12);
 
    return 0;
}


