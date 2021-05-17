#include "utility.h"

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

