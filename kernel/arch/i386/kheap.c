#define KHEAP_MAIN
#include <kernel/kheap.h>

//static functions
static uint32_t kmalloc_internal(uint32_t size, uint32_t align, uint32_t* physical_address);

//global variables
//uint32_t placement_addr;
extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;

//wrapper functions for public use

uint32_t kmalloc_a(uint32_t size){
    return kmalloc_internal(size, KHEAP_ALIGNED, NULL);
}

uint32_t kmalloc_p(uint32_t size, uint32_t* phys_addr){
    return kmalloc_internal(size, KHEAP_NOT_ALIGNED, phys_addr);
}

uint32_t kmalloc_ap(uint32_t size, uint32_t* phys_addr){
    return kmalloc_internal(size, KHEAP_ALIGNED, phys_addr);
} 

uint32_t kmalloc(uint32_t size){
    return kmalloc_internal(size, KHEAP_NOT_ALIGNED, NULL);
}


static uint32_t kmalloc_internal(uint32_t size, uint32_t isAligned, uint32_t* physical_address){

    if(isAligned == 1 && (placement_addr & 0xFFFFF000) ){ //if address is not already page aligned
        placement_addr &= 0xFFFFF000; //mask off values less than 4KB
        placement_addr += 0x1000; //advance pointer to 4 KB multiple
    }

    if(physical_address){ //if pointer exists, set to placement address
        *physical_address = placement_addr;
    }

    uint32_t addr = placement_addr; //set to memory address that pointer is referring to
    placement_addr += size; //increment pointer by size
    return addr;
}
