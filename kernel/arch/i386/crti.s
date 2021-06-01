.section .init
.global _init
.type _init, @function
_init:
        push ebp
        mov ebp, esp
        /* gcc will place the content of crtbegin.o's init section here */

.section .fini
global _fini:function
_fini:
        push ebp
        mov ebp, esp
        /* gcc will place the content of crtbegin.o's init section here */
