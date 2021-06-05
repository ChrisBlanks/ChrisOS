#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

static bool print(const char* data, size_t length){
    const unsigned char* bytes = (const unsigned char*) data;
    for(size_t i = 0; i < length; i++){
        if(putchar(bytes[i]) == EOF){
            return false;
        }
    }
    return true;
}

static bool printSignedInteger(int number){

#if defined(__is_libk)

    if(number < 0){ //if negative, write a "-"
        putchar('-');
        terminalPutNumber( (uint32_t) (-1* number));
    } else {
        terminalPutNumber(number);
    }

#else
    //To-do: Implement stdio and the write system call for libc
#endif

    return true;

}

int printf(const char* restrict format, ...){
    va_list parameters;
    va_start(parameters,format);

    int written = 0;

    while(*format != '\0'){
        size_t maxrem = INT_MAX - written;

        if(format[0] != '%'|| format[1] == '%'){
            if(format[0] == '%'){
               format++;
            }

            size_t amount = 1;
            while(format[amount] && format[amount] != '%'){
                amount++;
            }

            if(maxrem < amount){
                //To-Do: Set errno to EOVERFLOW
                return -1;
            }

            if (!print(format, amount)){
                return -1;
            }

            format += amount;
            written += amount;
            continue;

        }

        const char* format_begun_at = format++;

        if(*format == 'c'){
            format++;
            char c = (char) va_arg(parameters,int /* char promotes to int*/);

            if(!maxrem){
                //To-Do: Set errno to EOVERFLOW
                return -1;
            }

            if(!print(&c, sizeof(c))){
                return -1;
            }

            written++;

        } else if(*format == 's'){
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if(maxrem < len){
                //To-Do: Set errno EOVERFLOW
                return -1;
            }

            if(!print(str,len)){
                return -1;
            }
            written += len;

        } else if(*format == 'd'){
            format++;
            int integer = va_arg(parameters, int);
            int temp = (integer >= 0) ? integer : -1 * integer; //make positive for later computation

            if(!printSignedInteger(integer)){
                return -1;
            }

            if(integer < 0 || integer == 0){
                written++; //negative sign was written or only a 0 was written
            }
            
            while(temp > 0){ //count number of digits
                written++;
                temp /=10;
            }

        
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            
            if(maxrem < len){
                //To-Do: Set errno EOVERFLOW
                return -1;
            }

            if(!print(format, len)){
                return -1;
            }

            written += len;
            format += len;
        }

    }

    va_end(parameters);
    return written;
}