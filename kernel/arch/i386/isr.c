#include "isr.h"
#include <kernel/tty.h>

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
    
    terminalWriteString("Error Message: ");
    terminalWriteString(exception_messages[regs.int_no]);
    terminalWriteString("\n");

    for(;;); //halt system
}