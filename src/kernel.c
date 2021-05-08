#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Check if the compiler thinks you are targeting the wrong OS  
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble!"
#endif

// Check for proper target
#if !defined(__i386__)
#error "The only supported target is 32 bit ix86"
#endif

//defines
#define VGA_TEXT_MODE_BUFFER_ADDRESS 0xB8000


//global variables

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


/// Hardware text mode color constants
enum vga_color {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15,
};


//function definitions

///utility functions
static inline uint8_t vgaEntryColor(enum vga_color fg, enum vga_color bg){ 
    return fg | bg << 4; 
}

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color){
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
    size_t len = 0;

    while(str[len]){
        len++;
    }

    return len;
}


///Terminal related functions
void terminalInitialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vgaEntryColor(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) VGA_TEXT_MODE_BUFFER_ADDRESS;

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vgaEntry(' ', terminal_color);
        }
    }
}

void terminalSetColor(uint8_t color){
    terminal_color = color;
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

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y){
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vgaEntry(c,color);
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

void terminalWrite(const char* data, size_t size){
    for(size_t i = 0; i < size; i++){
        terminalPutChar(data[i]);
    }
}

void terminalWriteColorful(const char* data, size_t size){
    int current_color = VGA_COLOR_BLUE;

    for(size_t i = 0; i < size; i++){
        terminal_color = vgaEntryColor(current_color,VGA_COLOR_BLACK);
        terminalPutChar(data[i]); 

        if(++current_color > VGA_COLOR_WHITE){
            current_color = VGA_COLOR_BLUE;
        }
    }
}

void terminalWriteString(const char* data){
    terminalWrite(data,strlen(data));
}

void renderOSASCIIArt(){
    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

    terminal_color = vgaEntryColor(VGA_COLOR_RED,VGA_COLOR_BLACK);
    terminalWriteString(ascii_art);
}

void renderColorfulASCIIArt(){

    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

    terminalWriteColorful(ascii_art, strlen(ascii_art));

}

//Kernel Entry Point
void kernel_main(void){
    char* msg = "Hello, Kernel World!\n" 
                "This will continue on for quite a while," 
                "so that I can get a line break somewhere hahahahahahahahahaha\n";

    char* long_msg = "1This will be a very long message that will hopefully test scrolling\n"
                     "2second line: ffffffffffffffffffffffffffffffffffffffff\n"
                     "3\n"
                     "4\n5ffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                     "\n6a\n7b\n8c\n9d\n10e\n11f\n12g\n13h\n14i\n15j\n16k\n17l\n18m\n19n\n20o\n21p"
                     "fffffffffffffffffffffffffffffffffffffffff"
                     "\n22q\n23r\n24s\n25t\n26ffff\n27after everything";

    terminalInitialize();
    renderOSASCIIArt();
    renderColorfulASCIIArt();
    
    //test output
    //terminalWriteString(msg);
    //terminalWriteString(long_msg);
    
}


