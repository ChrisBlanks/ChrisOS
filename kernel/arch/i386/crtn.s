.section .init
        /* gcc will put the content of crtend.o's init section here */
        popl %ebp
        ret

.section .fini
        /* gcc will put the content of crtend.o's init section here */
        popl %ebp
        ret
