#ifndef _KHEAP_H_
#define _KHEAP_H_

#include <stddef.h>
#include <stdint.h>

#define KHEAP_NOT_ALIGNED 0
#define KHEAP_ALIGNED 1

uint32_t kmalloc_a(uint32_t size);                         // page aligned
uint32_t kmalloc_p(uint32_t size, uint32_t* phys_addr);    // returns a physical address
uint32_t kmalloc_ap(uint32_t size, uint32_t* phys_addr);   // page aligned & returns a physical address
uint32_t kmalloc(uint32_t size);

#endif