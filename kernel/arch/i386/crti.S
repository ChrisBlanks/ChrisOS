.section .init
.global _init
.type _init, @function
_init:
        push %ebp
        movl %esp, %ebp
        /* gcc will place the content of crtbegin.o's init section here */

.section .fini
.global _fini
.type _fini, @function
_fini:
        push %ebp
        movl %esp, %ebp
        /* gcc will place the content of crtbegin.o's init section here */