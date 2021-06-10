#include <kernel/paging.h>



void initializePaging(){

}


void switchPageDirectory(page_directory_t* new_page_dir){

}


page_t* getPage(uint32_t address, int createIfNonexistent,page_directory_t* page_dir){

}


void pageFault(registers_t regs){


}
