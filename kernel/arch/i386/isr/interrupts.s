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

    mov %ds, %ax  /* Move lower 16-bits of eax into ds (data segment) */
    push %eax /* Save the data segment descriptor */

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isrHandler  /* call C code to handle interrupt */

    pop %eax            /* reload the original data segement descriptor */
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa              /* restore/pop registers edi, esi, ebp, esp, ebx, edx, ecx, eax */

    add $0x08, %esp    /* Clean up the pushed error code and ISR number */
    sti
    iret              /* pops CS, EIP, EFLAGS, SS, and ESP */
      
	