#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

    int main(void) {
        void *handle;

        handle = dlopen ("/usr/lib/libcap.so.2", RTLD_LAZY);
        if (!handle) {
            exit(1);
        }

     sleep(60);

    dlclose(handle);
    exit(0);
    }
    
    
    