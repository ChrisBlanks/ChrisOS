.globl idt_flush

idt_flush:
    mov 4(%esp) , %eax /* Get the pointer to the IDT. Increment %esp index by 4 */
    lidt (%eax) /* Load Global Interrupt Descriptor */
    ret