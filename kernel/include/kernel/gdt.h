/*
 * Global Descriptor Table (GDT) Definitions
 *
 * 
 */

#ifndef _GDT_H
#define _GDT_H

#include <stddef.h>
#include <stdint.h>

/*
 * Access byte format
 *  |    7    | 6 ... 5     | 4          | 3          | 2              |  1     |   0       | 
 *  |segment  | Descriptor  | Descriptor | Executable | Direction      |R/W bit | Accessed? |
 *  |present? | Privilege   | type       | Bit        | or             |        | (reserved)|
 *  |         | Level       |            |1 for enable| Conforming bit |        |
 *  |         | (ring 0-3)  |
 */  

/*
 * Granularity byte format
 *  |    7       | 6            | 5        | 4        | 3 ... 0 | 
 *  |Granularity | Operand size | Reserved | Reserved | Segment |
 *  |'0'=1 byte  | '0'=16 bit   | val='0'  | val='0'  | length  |
 *  |'1'=1kib    | '1'=32 bit   |
 * 
 */  

//limit = 20-bit value for indicating the maximum addressable unit
// base = 32-bit value containing the lienar address where the segment begins

typedef struct __attribute__((packed)) gdt_entry_struct { //packed attribute retains alignment in structure
    uint16_t limit_low;  // lower 16-bits of the limit
    uint16_t base_low;   // lower 16 bits of the base
    uint8_t base_mid;    // middle 8 bits of base
    uint8_t access;      // access flags, which determine what ring the gdt segment can be used in
    uint8_t granularity; // describes segment configuration
    uint8_t base_high;   // last 8 bits of base
}  gdt_entry_t; 

typedef struct __attribute__((packed)) gdt_ptr_struct { //packed attribute retains alignment in structure
    uint16_t limit; // high 16-bits of all selector values
    uint32_t base;  // address of the 1st gdt_entry_t struct
} gdt_ptr_t;


//function prototype
void initGDT(void);

#endif