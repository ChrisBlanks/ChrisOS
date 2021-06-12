//kernel includes
#include <kernel/paging.h>
#include <kernel/kheap.h>
#include <kernel/tty.h>

//i386
#include "frame.h"
#include "utility.h"

//libk includes
#include <string.h>

page_directory_t* kernel_directory=0;
page_directory_t* current_directory=0;


void initializePaging(){
    uint32_t mem_end_page = DEFAULT_PHYSICAL_MEMORY_SIZE; //size of physical memory

    numFrames = mem_end_page / 0x1000;
    frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(numFrames)); //allocate memory address for frames
    memset(frames,0,INDEX_FROM_BIT(numFrames)); //set all values to 0

    kernel_directory = (page_directory_t*)kmalloc_a( sizeof(page_directory_t) ); 
    memset(kernel_directory, 0,sizeof(page_directory_t));
    current_directory = kernel_directory;

   // We need to identity map (phys addr = virt addr) from
   // 0x0 to the end of used memory, so we can access this
   // transparently, as if paging wasn't enabled.
   // NOTE that we use a while loop here deliberately.
   // inside the loop body we actually change placement_address
   // by calling kmalloc(). A while loop causes this to be
   // computed on-the-fly rather than once at the start.
   int i = 0;
   while (i < placement_addr)
   {
       // Kernel code is readable but not writeable from userspace.
       allocFrame( getPage(i, CREATE_PAGE_IF_NONEXISTENT, kernel_directory), !IS_KERNEL, !IS_WRITEABLE);
       i += 0x1000;
   }

    registerInterruptHandler(0x0E, &pageFault);
    switchPageDirectory(kernel_directory);   
}


//switches to specified page directory
void switchPageDirectory(page_directory_t* new_page_dir){
    current_directory = new_page_dir;
    
    asm volatile("mov %0, %%cr3":: "r"(&new_page_dir->tables_physical_addr));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; //enable paging
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}


//returns a pointer to the page entry at an address
page_t* getPage(uint32_t address, uint32_t createIfNonexistent,page_directory_t* page_dir){
    address /= 0x1000;

    uint32_t table_index = address/ 1024;
    if(page_dir->tables[table_index]){
        return &page_dir->tables[table_index]->pages[address % 1024];
    } else if(createIfNonexistent){ //if table does not exist && createIfNonexistent is true, create & return new entry
        uint32_t phys_addr;
        page_dir->tables[table_index] = (page_table_t*) kmalloc_ap(sizeof(page_table_t),&phys_addr); //create page aligned page directory
        memset(page_dir->tables[table_index],0, 0x1000);
        
        page_dir->tables_physical_addr[table_index] = phys_addr | 0x7; //set present, r/w, and US bits

        return &page_dir->tables[table_index]->pages[address % 1024]; 
    }else{
        return 0;
    }

}


void pageFault(registers_t regs){

    uint32_t faulting_addr; //faulting address is stored in the CR2 register

    asm volatile("mov %%cr2, %0" : "=r" (faulting_addr));

    // The error code gives us details of what happened.
    int present = !(regs.err_code & 0x1);   // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

    terminalWriteString("Page fault! (");

    if(present){
        terminalWriteString("present ");
    }

    if(rw){
        terminalWriteString("read-only ");
    }

    if(us){
        terminalWriteString("user-mode ");
    }

    if(reserved){
        terminalWriteString("reserved ");
    }
    
    terminalWriteString(") @ memory address ");
    terminalPutNumber(faulting_addr); //To-Do: replace with hex function
    terminalWriteString("(decimal)\n");
}
