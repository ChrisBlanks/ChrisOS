.globl idt_flush

.extern idt_ptr

idt_flush:
    
    lidt (idt_ptr)
    sti
    ret
