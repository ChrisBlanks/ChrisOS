#include <kernel/idt.h>
#include <string.h>

#include "utility.h"

extern void idt_flush();

//static function prototypes
static void init_idt(void);
static void idt_set_gate(uint8_t index, uint32_t base, uint16_t selector, uint8_t flags);
static void remapPIC(void); //remap the Programmable Interrupt Controller

//define macros
#define DEFAULT_IDT_SIZE 256

#define MASTER_PIC 0x20
#define SLAVE_PIC  0xA0

#define MASTER_COMMAND	MASTER_PIC
#define MASTER_DATA	(MASTER_PIC + 1)
#define SLAVE_COMMAND	SLAVE_PIC
#define SLAVE_DATA	(SLAVE_PIC+1)

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */


__attribute__((aligned(0x10))) idt_entry_t idt_entries[DEFAULT_IDT_SIZE]; //align for performance
idt_ptr_t idt_ptr;


void initIDT(void){
    init_idt();
    remapPIC();
}


static void init_idt(void){
    idt_ptr.limit = (sizeof(idt_entry_t) * DEFAULT_IDT_SIZE) -1 ;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries,0,sizeof(sizeof(idt_entry_t) * DEFAULT_IDT_SIZE));

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_flush();
}

static void idt_set_gate(uint8_t index, uint32_t base, uint16_t selector, uint8_t flags){
    idt_entries[index].base_low = (base & 0xFFFF);
    idt_entries[index].base_high = (base >> 16) & 0xFFFF;

    idt_entries[index].selector = selector;
    idt_entries[index].always_0 = 0;    
    idt_entries[index].flags = flags; // To-Do: add this when user-mode is used later on `| 0x60`
}

/*
 * Remap Programmable Interrupt Controller to avoid conflict w/ exceptions.
 * 
 * Master PIC: command port = 0x20, data port = 0x21
 * Slave PIC: command port = 0xA0, data port = 0xA1
 */
static void remapPIC(void){

    //start initialization sequence in cascade mode
    outb(MASTER_COMMAND, ICW1_INIT | ICW1_ICW4); 
    outb(SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);

    //write to the data registers
    outb(MASTER_DATA, 0x20);
    outb(SLAVE_DATA, 0x28);

    outb(MASTER_DATA, 0x04); //indicate to master PIC that slave PIC is at IRQ2
    outb(SLAVE_DATA, 0x02);  //assign "2" as slave PIC's cascade identity
    
    outb(MASTER_DATA, ICW4_8086); //set 8086/88 mode
    outb(SLAVE_DATA, ICW4_8086);
    
    outb(MASTER_DATA, 0x0);
    outb(SLAVE_DATA, 0x0);

    //assign interrupt requests to idt
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);

    idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

}