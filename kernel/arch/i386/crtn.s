.section .init
        /* gcc will put the content of crtend.o's init section here */
        pop ebp
        ret

.section .fini
        /* gcc will put the content of crtend.o's init section here */
        pop ebp
        ret
