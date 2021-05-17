#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stdint.h>

//define macros
#define VGA_CONTROL_REGISTER 0x3D4
#define VGA_DATA_REGISTER    0x3D5

#define VGA_CURSOR_START_REGISTER 0x0A 
#define VGA_CURSOR_END_REGISTER   0x0B
#define VGA_CURSOR_LOCATION_LOW   0x0F
#define VGA_CURSOR_LOCATION_HIGH  0x0E

#define VGA_TEXT_MODE_BUFFER_ADDRESS 0xB8000

/*
 * VGA Controller Word format (16 bits)
 * |15  ...  12 | 11 ...   8 |7  ...   0|
 * |background  | foreground | character| 
 * |color       | color      | code     |
 */


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

///utility functions
static inline uint8_t vgaEntryColor(enum vga_color fg, enum vga_color bg){ 
    return fg | bg << 4; 
}

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color){
    return (uint16_t) uc | (uint16_t) color << 8;
}


#endif