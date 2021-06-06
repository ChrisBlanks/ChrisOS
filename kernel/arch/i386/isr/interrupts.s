.globl isr0
.globl isr1
.globl isr2
.globl isr3
.globl isr4
.globl isr5
.globl isr6
.globl isr7
.globl isr8
.globl isr9
.globl isr10
.globl isr11
.globl isr12
.globl isr13
.globl isr14
.globl isr15
.globl isr16
.globl isr17
.globl isr18
.globl isr19
.globl isr20
.globl isr21
.globl isr22
.globl isr23
.globl isr24
.globl isr25
.globl isr26
.globl isr27
.globl isr28
.globl isr29
.globl isr30
.globl isr31


.globl irq0
.globl irq1
.globl irq2
.globl irq3
.globl irq4
.globl irq5
.globl irq6
.globl irq7
.globl irq8
.globl irq9
.globl irq10
.globl irq11
.globl irq12
.globl irq13
.globl irq14
.globl irq15


.type isr0, @function
.type isr1, @function
.type isr2, @function
.type isr3, @function
.type isr4, @function
.type isr5, @function
.type isr6, @function
.type isr7, @function
.type isr8, @function
.type isr9, @function

.type isr10, @function
.type isr11, @function
.type isr12, @function
.type isr13, @function
.type isr14, @function
.type isr15, @function
.type isr16, @function
.type isr17, @function
.type isr18, @function
.type isr19, @function

.type isr20, @function
.type isr21, @function
.type isr22, @function
.type isr23, @function
.type isr24, @function
.type isr25, @function
.type isr26, @function
.type isr27, @function
.type isr28, @function
.type isr29, @function
.type isr30, @function
.type isr31, @function

.type irq0, @function
.type irq1, @function
.type irq2, @function
.type irq3, @function
.type irq4, @function
.type irq5, @function
.type irq6, @function
.type irq7, @function
.type irq8, @function
.type irq9, @function

.type irq10, @function
.type irq11, @function
.type irq12, @function
.type irq13, @function
.type irq14, @function
.type irq15, @function


isr0:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x0         /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr1:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x1          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr2:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x2          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr3:
    cli              /* clear/disable interrupts */
    push $0x0          /* push a dummy error code */
    push $0x3           /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr4:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x4          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr5:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x5          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr6:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x6          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr7:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x7          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr8:
    cli                  /* clear/disable interrupts */
    push   $0x8          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr9:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x9          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr10:
    cli                  /* clear/disable interrupts */
    push   $0xA         /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr11:
    cli                  /* clear/disable interrupts */
    push   $0xB          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr12:
    cli                  /* clear/disable interrupts */
    push   $0xC         /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr13:
    cli                  /* clear/disable interrupts */
    push   $0xD          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
isr14:
    cli                  /* clear/disable interrupts */
    push   $0xE          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr15:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0xF         /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr16:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x10          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr17:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x11           /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr18:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x12          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr19:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x13          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr20:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x14         /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr21:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x15          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr22:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x16          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr23:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x17          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr24:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x18          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr25:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x19          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr26:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x1A          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr27:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x1B          /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr28:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x1C           /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr29:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x1D           /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr30:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x1E        /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/

isr31:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x20           /* push interrupt number */

    jmp isr_common_stub  /* jumpt to common handler*/


.extern isrHandler

isr_common_stub:
    pusha  /* push general purpose registers edi, esi, ebp, esp, ebx, edx, ecx, eax  */
    push %ds
    push %es
    push %fs
    push %gs

    /*mov %ds, %ax  /* Move lower 16-bits of eax into ds (data segment) */
    /*push %eax /* Save the data segment descriptor */

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isrHandler  /* call C code to handle interrupt */

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa              /* restore/pop registers edi, esi, ebp, esp, ebx, edx, ecx, eax */

    add $0x08, %esp    /* Clean up the pushed error code and ISR number */
    sti
    iret              /* pops CS, EIP, EFLAGS, SS, and ESP */
      


irq0:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x32         /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq1:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x33          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq2:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x34          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq3:
    cli              /* clear/disable interrupts */
    push $0x0          /* push a dummy error code */
    push $0x35           /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq4:
    cli                  /* clear/disable interrupts */
    push $0x0         /* push a dummy error code */
    push $0x36          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq5:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x37          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq6:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x38          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq7:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x39          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq8:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x40          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq9:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x41          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq10:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x42        /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq11:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x43          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq12:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x44         /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq13:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x45          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

/* Pushes its own error code */
irq14:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x46          /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/

irq15:
    cli                  /* clear/disable interrupts */
    push   $0x0         /* push a dummy error code */
    push   $0x47         /* push interrupt number */

    jmp irq_common_stub  /* jumpt to common handler*/



.extern irqHandler


irq_common_stub:
    pusha  /* push general purpose registers edi, esi, ebp, esp, ebx, edx, ecx, eax  */
    push %ds
    push %es
    push %fs
    push %gs

    /*mov %ds, %ax  /* Move lower 16-bits of eax into ds (data segment) */
    /*push %eax /* Save the data segment descriptor */

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call irqHandler  /* call C code to handle interrupt */

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa              /* restore/pop registers edi, esi, ebp, esp, ebx, edx, ecx, eax */

    add $0x08, %esp    /* Clean up the pushed error code and ISR number */
    sti
    iret              /* pops CS, EIP, EFLAGS, SS, and ESP */
      