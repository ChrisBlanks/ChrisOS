
#ifndef _ISR_H
#define _ISR_H

#include <stddef.h>
#include <stdint.h>


#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47


typedef struct __attribute__((packed)) registers{
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
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


typedef void (*isr_t)(registers_t);

void isrHandler(registers_t regs);
void irqHandler(registers_t regs);
void registerInterruptHandler(uint8_t num, isr_t handler);

#endif