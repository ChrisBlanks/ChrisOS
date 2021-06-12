#ifndef _PAGING_H_
#define _PAGING_H_

#include <stddef.h>
#include <stdint.h>

#include <kernel/isr.h>

#define DEFAULT_NUMBER_OF_PAGES  1024
#define DEFAULT_NUMBER_OF_TABLES 1024

#define CREATE_PAGE_IF_NONEXISTENT 1
#define DO_NOT_CREATE_PAGE_IF_NONEXISTENT 0

//16 MB
#define DEFAULT_PHYSICAL_MEMORY_SIZE 0x10000000  

typedef struct page_t {
    uint32_t present    : 1;   // Page present in memory
    uint32_t rw         : 1;   // Read-only if clear, readwrite if set
    uint32_t user       : 1;   // Supervisor level only if clear
    uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
    uint32_t dirty      : 1;   // Has the page been written to since last refresh?
    uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
    uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table_t {
    page_t pages[DEFAULT_NUMBER_OF_PAGES];
} page_table_t;

typedef struct page_directory_t {
    page_table_t* tables[DEFAULT_NUMBER_OF_TABLES];
    uint32_t tables_physical_addr[DEFAULT_NUMBER_OF_TABLES]; //array of physical address pointers to page tables (loaded int CR3 register)
    uint32_t physical_addr; //physical address of 'tables_physical_addr' struct member
} page_directory_t;


void initializePaging(); //setups of environment for paging
void switchPageDirectory(page_directory_t* new_page_dir); //loads page directory into CR3 register
page_t* getPage(uint32_t address, uint32_t createIfNonexistent, page_directory_t* page_dir); //retrieves a pointer to a page 
void pageFault(registers_t regs);

#endif