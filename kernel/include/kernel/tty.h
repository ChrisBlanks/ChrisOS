#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

//public functiosn for manipulating the cursor 
void cursorDisable(void);
void cursorEnable(uint8_t cursor_start, uint8_t cursor_end);
uint16_t cursorPosition(void);
void cursorUpdate(int x_pos,int y_pos);

//public functions for manipulating the terminal
void terminalClear(void);
void terminalInitialize(void);
void terminalSetColor(uint8_t color);
void terminalPutChar(char c);
void terminalWrite(const char* data, size_t size);
void terminalWriteString(const char* data);

#endif