#include "utility.h"
#include <kernel/tty.h>


void panic(const char* msg, const char* src_file,uint32_t line_num){
    asm volatile("cli"); //disable interrupts

    terminalWriteString("PANIC( ");
    terminalWriteString(msg);
    terminalWriteString(") @ ");
    terminalWriteString(src_file);
    terminalWriteString(":");
    terminalPutNumber(line_num);
    terminalWriteString("\n");

    for(;;); //halt by entering an infinite loop
}


/*
 * Write a 'value' to specified 'port' via assembly call
 */
void outb(uint16_t port, uint8_t value){
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value) );
}

/*
 * Read 8-bit 'value' from specified 'port' via assembly call
 */
uint8_t inb(uint16_t port){
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a" (value) : "dN" (port) );
    return value;
}

/*
 * Read 16-bit 'value' from specified 'port' via assembly call
 */
uint16_t inw(uint16_t port){
    uint16_t value;
    asm volatile ("inw %1, %0" : "=a" (value) : "dN" (port) );
    return value;
}

