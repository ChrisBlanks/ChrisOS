#include <kernel/isr.h>
#include <kernel/tty.h>
#include "utility.h"

#define DEFAULT_INTERRUPT_HANDLERS_SIZE 256

#define MASTER_PIC 0x20
#define SLAVE_PIC  0xA0

#define MASTER_COMMAND	MASTER_PIC
#define MASTER_DATA	(MASTER_PIC + 1)
#define SLAVE_COMMAND	SLAVE_PIC
#define SLAVE_DATA	(SLAVE_PIC+1)


isr_t interrupt_handlers[DEFAULT_INTERRUPT_HANDLERS_SIZE] = {0};

/* Exception descriptions */
char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


//Interrupt Service Routines (ISR) callback
void isrHandler(registers_t regs){

    terminalWriteString("Received interrupt: ");
    terminalPutNumber(regs.int_no);//write interrupt number
    terminalWriteString("\n");

    terminalWriteString("Error code: ");
    terminalPutNumber(regs.err_code);//write error code
    terminalWriteString("\n");
    
    terminalWriteString("Error Message: ");
    terminalWriteString(exception_messages[regs.int_no]);
    terminalWriteString("\n");

    for(;;); //halt system
}

// Interrupt Request callback
void irqHandler(registers_t regs){

    //execute custom handler
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

    if(regs.int_no >= 40){ //send an end-of-interrupt signal to PICS if slave PIC
        outb(SLAVE_PIC,0x20); //send reset signal to slave PIC
    }

    outb(MASTER_PIC,0x20); //send reset signal to master PIC

}

// set a custom handler for IRQ sepcified by 'num'
void registerInterruptHandler(uint8_t num, isr_t handler){
    interrupt_handlers[num] = handler;
}