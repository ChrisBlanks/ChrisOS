#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"


//define macros
#define VGA_TEXT_MODE_BUFFER_ADDRESS 0xB8000

//function prototypes of private functions
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y);
void scrollTerminalDown();

//global variables
static uint16_t* const VGA_MEMORY_ADDR = (uint16_t*) VGA_TEXT_MODE_BUFFER_ADDRESS;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

//function definitions

void terminalInitialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vgaEntryColor(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY_ADDR;

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vgaEntry(' ', terminal_color);
        }
    }
}


void terminalPutChar(char c){
    if(c == '\n'){ //if newline character, advance to the next line
        terminal_column = 0;

        if(++terminal_row == VGA_HEIGHT){ //handle if end of terminal vertical bound
            scrollTerminalDown();
        }
        return;
    }

    terminalPutEntryAt(c,terminal_color, terminal_column,terminal_row);
    
    if(++terminal_column == VGA_WIDTH){ //handle if end of terminal horizontal bound
        terminal_column = 0;

        if(++terminal_row == VGA_HEIGHT){ //handle if end of terminal vertical bound
            scrollTerminalDown();
        }
    }
}


void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y){
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vgaEntry(c,color);
}


void terminalSetColor(uint8_t color){
    terminal_color = color;
}


void terminalWrite(const char* data, size_t size){
    for(size_t i = 0; i < size; i++){
        terminalPutChar(data[i]);
    }
}


void terminalWriteString(const char* data){
    terminalWrite(data,strlen(data));
}


void scrollTerminalDown(){

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){

            const size_t index = y * VGA_WIDTH + x;
            
            if(y < VGA_HEIGHT - 1 ){ //copy row+1 into row
                const size_t index_next_row = (y+1) * VGA_WIDTH + x; 
                terminal_buffer[index] = terminal_buffer[index_next_row];
            } else { //fill last row w/ spaces
                terminal_buffer[index] = vgaEntry(' ', terminal_color); 
            }
        }
    }

    terminal_row =  VGA_HEIGHT - 1; //set position to last row
}