 /* GNU AS assembly syntax */
 
 /*
  * %ax 16 bit register
  */

.globl gdt_flush /* Make this routine available to C code */

.extern gdt_ptr

gdt_flush:
   lgdt (gdt_ptr)        /* Load the new GDT pointer */
   
   mov $0x10, %ax     /* 0x10 is the offset in the GDT to the data segment */
                      /* Load all data segement selectors */
   mov %ax, %ds       
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   mov %ax, %ss

   jmp $0x08,$flush  /* far jump to code segment w/ 0x08 offset */ 

flush:
   ret           