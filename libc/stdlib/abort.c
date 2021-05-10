#include <stdio.h>
#include <stdlib.h>

__attribute__((__no_return__))
void abort(void){
#if defined(__is_libk)
    //To-Do: Add proper kernel panic
    printf("kernel: panic: abort()\n");
#else
    printf("abort()\n");
#endif

    while(1){ }
    __builtin_unreachable();

}