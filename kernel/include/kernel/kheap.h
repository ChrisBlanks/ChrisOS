#ifndef _KHEAP_H_
#define _KHEAP_H_

#include <stddef.h>
#include <stdint.h>

#include <kernel/ordered_array.h>


#define KHEAP_START        0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define KHEAP_INDEX_SIZE   0x20000
#define KHEAP_MIN_SIZE     0x70000
#define KHEAP_MAGIC        0xDEADBEEF

#define KHEAP_NOT_ALIGNED 0
#define KHEAP_ALIGNED 1

#define IS_READ_ONLY 1
#define IS_SUPERVISOR_MODE 1

typedef struct header_t {
    uint32_t magic; //magic number used for error checking & identification 
    uint8_t isHole; // 1 if memory is open (a hole), 0 otherwise
    uint32_t size;  //size of block (header + data + footer)
} header_t;

typedef struct footer_t {
    uint32_t magic;
    header_t* header_ref; //pointer to header in memory
} footer_t;

typedef struct heap_t {
    ordered_array_t index;  //index of items

    uint32_t start_address;     //start of allocated space
    uint32_t end_address;       //end of allocated space; can be expanded
    uint32_t max_address;       //maximum address that the heap can be expanded to
    uint8_t isSupervisorMode;   // if 1, supervisor-only usage
    uint8_t isReadOnly;         // if 1, pages are read-only
} heap_t;


//heap_t* createHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t isSupervisorMode, uint8_t isReadOnly);
heap_t* createHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t isSupervisorMode, uint8_t isReadOnly);
void* allocHeap(uint32_t size, uint8_t pageAligned, heap_t* heap);
void freeHeap(void* p, heap_t* heap);

uint32_t kmalloc_a(uint32_t size);                         // page aligned
uint32_t kmalloc_p(uint32_t size, uint32_t* phys_addr);    // returns a physical address
uint32_t kmalloc_ap(uint32_t size, uint32_t* phys_addr);   // page aligned & returns a physical address
uint32_t kmalloc(uint32_t size);
void kfree(void* p);

#endif