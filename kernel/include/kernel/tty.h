#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

//public functions for manipulating the terminal 
void terminalInitialize(void);
void terminalSetColor(uint8_t color);
void terminalPutChar(char c);
void terminalWrite(const char* data, size_t size);
void terminalWriteString(const char* data);

#endif