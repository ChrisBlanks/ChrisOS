#include <kernel/gdt.h>

#define DEFAULT_ENTRY_ARRAY_SIZE 5

extern void gdt_flush(); //defined in assembly file

//global variables
gdt_entry_t gdt_entries[DEFAULT_ENTRY_ARRAY_SIZE];
gdt_ptr_t gdt_ptr;

//static function prototypes
static void createInitialGDTEntries(void);
static void setGDTEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);


void initGDT(void){
    createInitialGDTEntries();
}


static void createInitialGDTEntries(void){
    gdt_ptr.limit = (sizeof(gdt_entry_t) * DEFAULT_ENTRY_ARRAY_SIZE) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    setGDTEntry(0,0,0,0,0); //create null segment

    //0xFFFFFFFF = 4 GiB
    setGDTEntry(1,0,0xFFFFFFFF,0x9A,0xCF); //create code segment (CS), which tells the CPU which offset in the gdt has access privileges to execute code
    setGDTEntry(2,0,0xFFFFFFFF,0x92,0xCF); //create data segment (DS), which tells the CPU the access privileges for the current data 
    setGDTEntry(3,0,0xFFFFFFFF,0xFA,0xCF); //create user mode code segment
    setGDTEntry(4,0,0xFFFFFFFF,0xF2,0xCF); //create user mode data segment

    gdt_flush();

}

static void setGDTEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity){
    gdt_entries[index].base_low =  (  base & 0xFFFF); //get lower 16 bits
    gdt_entries[index].base_mid =  ( (base >> 16) & 0xFF); //get mid 8 bit
    gdt_entries[index].base_high = ( (base >> 24) & 0xFF); //get high 8 bits
    
    gdt_entries[index].limit_low = (limit & 0xFFFF); //get lower 16 bits
    gdt_entries[index].granularity = ((limit >> 16) & 0x0F); //shift out lower 16 bits & mask off upper nibble to get the segment length
    gdt_entries[index].granularity |= (granularity & 0xF0); //mask off lower 4 bits of granularity & OR it w/ previous operation
    gdt_entries[index].access = access; 
    
}
