
#ifndef _ISR_H
#define _ISR_H

#include <stddef.h>
#include <stdint.h>

typedef struct __attribute__((packed)) registers{
    uint32_t ds;  //data segement selector
    
    //pushed by pusha assembly command
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    
    //interrupt number & error code
    uint32_t int_no;
    uint32_t err_code;

    // pushed by the processor automatically
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
} registers_t ;

void isrHandler(registers_t* regs);

#endif