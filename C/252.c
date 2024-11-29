#include <stdio.h>

int main() {
    #if defined(_POSIX_C_SOURCE)
        printf("_POSIX_C_SOURCE = %ld\n", _POSIX_C_SOURCE);
    #else
        printf("_POSIX_C_SOURCE is not defined\n");
    #endif
    
    #if defined(_POSIX_VERSION)
        printf("_POSIX_VERSION = %ld\n", _POSIX_VERSION);
    #else
        printf("_POSIX_VERSION is not defined\n");
    #endif
    
    return 0;
}
