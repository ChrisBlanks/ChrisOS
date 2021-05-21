/*
 * Interrupt Descriptor Table (IDT) Definitions
 *
 * Tells the processor where to find handlers for each interrupt
 */

#ifndef _IDT_H
#define _IDT_H

#include <stddef.h>
#include <stdint.h>


/*
 * Granularity byte format
 *  |    7       | 6    ... 5   | 4 ... 0         | 
 *  | Present?   |      DPL     | Always '0b00110'|
 *  |            |              |                 |
 *  |            |              |
 *    If present bit is not set, causes a "Interrupt Not Handled" exception
 */   

typedef struct __attribute__((packed)) idt_entry_struct {
    uint16_t base_low;
    uint16_t selector;    //  Kernel segment selector
    uint8_t always_0;     // always set to 0
    uint8_t flags;        // flags
    uint16_t base_high;   // high 16-bits of the address to jump to
} idt_entry_t;

//pointer to array of interrupt handlers
typedef struct __attribute__((packed)) idt_ptr_struct {
    uint16_t limit;
    uint32_t base;  //address of the 1st element in the array of idt_entry_t's
} idt_ptr_t;

//Extern directives access the addresses of ASM ISR handlers
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


#endif