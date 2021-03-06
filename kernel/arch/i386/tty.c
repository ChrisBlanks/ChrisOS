#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"
#include "utility.h"

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
void cursorDisable(void){

    /// prepare cursor start register
    outb(VGA_CONTROL_REGISTER,VGA_CURSOR_START_REGISTER);

    /// write a '1' to bit 5 to disable cursor
    outb(VGA_DATA_REGISTER, 0x20);
}


void cursorEnable(uint8_t cursor_start, uint8_t cursor_end){
    //enable cursor start register

    ///prepare cursor start register
    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_START_REGISTER);

    /// read current value & mask off lower 6 bits
    /// bit 5 should be '0' to enable cursor
    /// mask off top 3 bits of cursor_start
    outb(VGA_DATA_REGISTER, ( inb(VGA_DATA_REGISTER) & 0xC0 )  | (cursor_start & 0x1F) ); 
    

    /// enable cursor end label

    /// prepare cursor end register
    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_END_REGISTER);

    /// read current value & mask off lower 5 bits
    /// mask off top 3 bits of cursor_end
    outb(VGA_DATA_REGISTER, ( inb(VGA_DATA_REGISTER) & 0xE0 ) | (cursor_end & 0x1F) ) ;
}


uint16_t cursorPosition(void){
    uint16_t pos = 0;

    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_LOCATION_LOW);
    pos |= inb(VGA_DATA_REGISTER); //read lower byte into pos


    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_LOCATION_HIGH);
    pos |= ((uint16_t)inb(VGA_DATA_REGISTER)) << 8; //read higher byte into pos & shift up a byte

    return pos;
}

//To-Do: Figure out how to get a vertical cursor for left & right
void cursorSetOriention(int pos){
    switch(pos){
        case CURSOR_LOCATION_BOTTOM:
            cursorEnable(15,31); 
            break;
        case CURSOR_LOCATION_TOP:
            cursorEnable(0,1); 
            break;
        case CURSOR_LOCATION_LEFT:
            //cursorEnable(10,15);  
            break;
        case CURSOR_LOCATION_RIGHT:
            //cursorEnable(15,31); 
            break;  
        case CURSOR_LOCATION_FILLED:
            cursorEnable(0,15); 
            break;          
    }
}

void cursorUpdate(int x_pos, int y_pos){
    uint16_t new_pos = y_pos * VGA_WIDTH + x_pos;

    /// prepare cursor location lower bits register
    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_LOCATION_LOW);

    /// mask lower byte of position before sending to data reg
    outb(VGA_DATA_REGISTER, (uint8_t) (new_pos & 0xFF) );

    /// prepare cursor location higher bits register
    outb(VGA_CONTROL_REGISTER, VGA_CURSOR_LOCATION_HIGH);

    /// shift upper byte of position & mask before sending to data reg
    outb(VGA_DATA_REGISTER, (uint8_t) ( (new_pos >> 8) & 0xFF) );
}


void terminalClear(void){

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vgaEntry(' ', terminal_color);
        }
    }

    //reset terminal row & column positions to initial position
    terminal_row = 0;
    terminal_column = 0;

}


void terminalInitialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vgaEntryColor(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY_ADDR;

    cursorSetOriention(CURSOR_LOCATION_BOTTOM);
    

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vgaEntry(' ', terminal_color);
        }
    }

    cursorUpdate(0,0); //set cursor to 0,0
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


void terminalPutHexNumber(uint32_t num){
    char parse_buf[11] = {0}; //max number of decimal digits of a 32-bit number is 10. Add index for null
    char num_str[11] = {0};
    uint32_t num_copy = num;
    uint32_t val, ascii_val;
    uint8_t firstNonZeroFound = 0;
    uint8_t result_index = 0;

    if(num == 0){ //handle simple case
        terminalWriteString("0");
        return;
    }

    for(int index=0;index < 10;index++){
        val = num_copy % 16;    
        if(val < 10){
            ascii_val = val + 48; //add offset to 'val' to calculate ascii value of number
        } else{
            ascii_val = (val %10) + 65; //add offset to remainder to calculate ascii capital letter 
        }

        parse_buf[index] = (char)ascii_val;

        num_copy = (uint32_t) (num_copy / 16); //shift digits for next calculation
    }

    /*Debug number parsing: 
    terminalWriteString("\nIntermediate result: ");
    terminalWriteString(parse_buf);
    terminalWriteString("\n");
    */
   
    for(int index=9;index>=0;index--){

        if( parse_buf[index] == '0'  && firstNonZeroFound == 0){
            continue; //skip index if equal to '0' & no nonzero characters have been found yet
        }
        num_str[result_index] = parse_buf[index];
        result_index++;
        firstNonZeroFound = 1;
    }

    terminalWriteString(num_str);
}

void terminalPutNumber(uint32_t num){
    char parse_buf[11] = {0}; //max number of decimal digits of a 32-bit number is 10. Add index for null
    char num_str[11] = {0};
    uint32_t num_copy = num;
    uint32_t val, ascii_val;
    uint8_t firstNonZeroFound = 0;
    uint8_t result_index = 0;

    if(num == 0){ //handle simple case
        terminalWriteString("0");
        return;
    }

    for(int index=0;index < 10;index++){
        val = num_copy % 10;    
        ascii_val = val + 48; //add offset to 'val' to calculate ascii value of number
        parse_buf[index] = (char)ascii_val;

        num_copy = (uint32_t) (num_copy / 10); //shift digits for next calculation
    }

    /*Debug number parsing:
    terminalWriteString("\nIntermediate result: ");
    terminalWriteString(parse_buf);
    terminalWriteString("\n");
    */
   
    for(int index=9;index>=0;index--){

        if( parse_buf[index] == '0'  && firstNonZeroFound == 0){
            continue; //skip index if equal to '0' & no nonzero characters have been found yet
        }
        num_str[result_index] = parse_buf[index];
        result_index++;
        firstNonZeroFound = 1;
    }

    terminalWriteString(num_str);
}


void terminalSetColor(uint8_t color){
    terminal_color = color;
}


void terminalWrite(const char* data, size_t size){
    for(size_t i = 0; i < size; i++){
        terminalPutChar(data[i]);
    }
    cursorUpdate(terminal_column, terminal_row); //update cursor
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