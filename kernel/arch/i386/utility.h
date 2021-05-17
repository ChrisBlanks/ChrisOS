#ifndef _KERNEL_UTILITY_H
#define _KERNEL_UTILITY_H

#include <stddef.h>
#include <stdint.h>

//functions for manipulating hardware registers
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#endif