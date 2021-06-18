#include <kernel/kheap.h>
#include <kernel/paging.h>
#include "frame.h"

#include <kernel/tty.h>

//static functions
static void expandHeap(uint32_t new_size, heap_t* heap);
static uint32_t contractHeap(uint32_t new_size, heap_t* heap);
static uint32_t kmalloc_internal(uint32_t size, uint32_t align, uint32_t* physical_address);
static int findSmallestHole(uint32_t size, uint8_t page_align, heap_t* heap);
static uint8_t headerLessThanComparison(void* a, void* b);

//global variables
extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;

heap_t* kheap= 0;


//heap functions
heap_t* createHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t isSupervisorMode, uint8_t isReadOnly){
    heap_t* heap_local = (heap_t*) kmalloc(sizeof(heap_t));
    
    if( (start % 0x1000) != 0 || (end % 0x1000) != 0){
        return; // if not page aligned, return NULL
    }

    heap_local->index = placeOrderedArray((void*)start, KHEAP_INDEX_SIZE, &headerLessThanComparison);

    start += sizeof(any_type_t) * KHEAP_INDEX_SIZE;

    if((start & 0xFFFFF000) != 0){
        start &= 0xFFFFF000;
        start += 0x1000;
    }

    heap_local->start_address = start;
    heap_local->end_address = end;
    heap_local->max_address = max;
    heap_local->isSupervisorMode = isSupervisorMode;
    heap_local->isReadOnly = isReadOnly;

    header_t* hole = (header_t*)start;
    hole->size = end - start;
    hole->magic = KHEAP_MAGIC;
    hole->isHole = 1;

    insertOrderedArray((void*)hole, &heap_local->index ); //insert hole into heap that spans the full heap
    
    return heap_local;
}

static void expandHeap(uint32_t new_size, heap_t* heap){
    if(new_size <= (heap->end_address - heap->start_address) ){ //if new size is less than or equal to current size, do nothing
        return;
    }

    if( (new_size & 0xFFFFF000) != 0){
        new_size &= 0xFFFFF000;
        new_size += 0x1000;
    }

    if(heap->start_address + new_size > heap->max_address ){ //check that new size doesn't extend past max address
        return;
    }

    uint32_t old_size = heap->end_address - heap->start_address;
    uint32_t index = old_size;

    while(index < new_size){
        allocFrame( getPage(heap->start_address + index, CREATE_PAGE_IF_NONEXISTENT, kernel_directory),
                    (heap->isSupervisorMode) ? 1 : 0,
                    (heap->isReadOnly) ? 0: 1
                    );
        index += 0x1000;
    }

    heap->end_address = heap->start_address + new_size;
}

static uint32_t contractHeap(uint32_t new_size, heap_t* heap){
    if(new_size >= heap->end_address - heap->start_address){
        return heap->end_address - heap->start_address; //return current size
    }

    //align on page boundary
    if(new_size & 0x1000){
        new_size &= 0x1000;
        new_size += 0x1000;
    }

    if(new_size < KHEAP_MIN_SIZE){ 
        new_size = KHEAP_MIN_SIZE;
    }

    uint32_t old_size = heap->end_address - heap->start_address;
    uint32_t bound = old_size - 0x1000;

    while(new_size < bound){
        freeFrame(getPage(heap->start_address + bound, DO_NOT_CREATE_PAGE_IF_NONEXISTENT, kernel_directory));
        bound -= 0x1000;
    }

    heap->end_address = heap->start_address + new_size;
    return new_size;
}

void* allocHeap(uint32_t size, uint8_t pageAligned, heap_t* heap){
    uint32_t new_size = size + sizeof(header_t) + sizeof(footer_t);
    int iterator = findSmallestHole(new_size, pageAligned, heap);

    if(iterator == -1){ //if couldn't find a suitable hole
        uint32_t old_length = heap->end_address - heap->start_address;
        uint32_t old_end_address = heap->end_address;

        expandHeap(old_length+new_size, heap); //expand heap

        //find the endmost header available
        uint32_t new_length = heap->end_address - heap->start_address;
        iterator = 0;
        int index = -1;
        uint32_t value = 0x0;

        while(iterator < (int) heap->index.size){
            uint32_t tmp = (uint32_t) lookupItemInOrderedArray(iterator, &heap->index);
            if(tmp > value){
                value = tmp;
                index = iterator;
            }
            iterator++;
        }

        if(index == -1){ //if no headers were found, create a header
            header_t* header = (header_t*)old_end_address;
            header->magic = KHEAP_MAGIC;
            header->size = new_length - old_length;
            header->isHole = 1;

            footer_t* footer = (footer_t*)((uint32_t)header+ header->size - sizeof(footer_t));
            footer->header_ref = header;
            footer->magic = KHEAP_MAGIC;
        } else{
            // The last header needs adjusting.
            header_t *header = lookupItemInOrderedArray(index, &heap->index);
            header->size += new_length - old_length;
            // Rewrite the footer.
            footer_t *footer = (footer_t *) ( (uint32_t)header + header->size - sizeof(footer_t) );
            footer->header_ref = header;
            footer->magic = KHEAP_MAGIC;
        }

        //recursive call now that space has been made
        return allocHeap(size,pageAligned,heap);
    }


    header_t* original_hole_header = (header_t*) lookupItemInOrderedArray(iterator, &heap->index);
    uint32_t original_hole_pos = (uint32_t)original_hole_header;
    uint32_t original_hole_size = original_hole_header->size;

    //check if filling the new hole doesn't leave enough room for a new hole to be made from
    if(original_hole_size - new_size < sizeof(header_t) + sizeof(footer_t)){
        size += original_hole_size - new_size;
        new_size = original_hole_size;
    }

    if(pageAligned && original_hole_pos & 0xFFFFF000){ //if page aligned, make a new hole in front our new block
        uint32_t new_location = original_hole_pos + 0x1000 - (original_hole_pos & 0xFFF) - sizeof(header_t);
        header_t* hole_header = (header_t*)original_hole_pos;
        hole_header->size = 0x1000 - (original_hole_pos & 0xFFF) - sizeof(header_t);

        hole_header->magic = KHEAP_MAGIC;
        hole_header->isHole = 1;

        footer_t* hole_footer = (footer_t*)((uint32_t)new_location - sizeof(footer_t));
        hole_footer->magic = KHEAP_MAGIC;
        hole_footer->header_ref = hole_header;

        original_hole_pos = new_location;
        original_hole_size = original_hole_size - hole_header->size;
    } else {
        removeItemInOrderedArray(iterator, &heap->index); //remove hole
    }

    //create a block of memory at position of hole
    header_t* block_header = (header_t*)original_hole_pos;
    block_header->magic = KHEAP_MAGIC;
    block_header->isHole = 0; 
    block_header->size = new_size;

    footer_t* block_footer = (footer_t*)(original_hole_pos+sizeof(header_t)+size);
    block_footer->magic = KHEAP_MAGIC;
    block_footer->header_ref = block_header;

    if(original_hole_size - new_size > 0){ //if leftover space from original hole, create a new hole
        header_t* hole_header = (header_t*)(original_hole_pos + sizeof(header_t) + size + sizeof(footer_t));
        hole_header->magic = KHEAP_MAGIC;
        hole_header->isHole = 1; 
        hole_header->size = original_hole_size - new_size;

        footer_t* hole_footer = (footer_t*)( (uint32_t)hole_header + original_hole_size - new_size - sizeof(footer_t) );
        if((uint32_t)hole_footer < heap->end_address){
            hole_footer->magic = KHEAP_MAGIC;
            hole_footer->header_ref = hole_header;
        }
        insertOrderedArray((void*)hole_header,&heap->index);
    }

    return (void*) ((uint32_t)block_header + sizeof(header_t));
}

void freeHeap(void*p, heap_t* heap){
    if(p == NULL){
        return;
    }

    header_t* header = (header_t*)( (uint32_t)p -sizeof(header_t) );
    footer_t* footer = (footer_t*)( (uint32_t)header + header->size - sizeof(footer_t));

    if(header->magic != KHEAP_MAGIC || footer->magic != KHEAP_MAGIC ){
        return;
    }

    header->isHole = 1;
    uint8_t do_add = 1; //boolean to control whether to add a header to the heap index

    //check if there's a hole in the memory before the current header, combine them
    footer_t* test_footer = (footer_t*)((uint32_t)header - sizeof(footer_t));
    if(test_footer->magic == KHEAP_MAGIC && test_footer->header_ref->isHole == 1){
        uint32_t cache_size = header->size;
        header = test_footer->header_ref; //change header reference to previous header;
        footer->header_ref = header; //update footer's header reference
        header->size += cache_size; //update size to be the size of both blocks of memory

        do_add = 0; //since this was a merge, no need to add a new entry
    }

    header_t* test_header = (header_t*)((uint32_t)footer + sizeof(footer_t));
    if(test_header->magic == KHEAP_MAGIC && test_header->isHole){
        header->size += test_header->size;
        test_footer = (footer_t*)((uint32_t)test_header + test_header->size - sizeof(footer_t));

        footer = test_footer;

        //loop through heap blocks to find header
        uint32_t iterator = 0;
        while( (iterator < heap->index.size) && (lookupItemInOrderedArray(iterator,&heap->index) != (void*)test_header )){
            iterator++;
        }

        if(iterator > heap->index.size){
            return; // iterator should not exceed index size
        }

        removeItemInOrderedArray(iterator, &heap->index);
    }

    if((uint32_t)footer+ sizeof(footer_t) == heap->end_address){
        uint32_t old_length = heap->end_address - heap->start_address;
        uint32_t new_length = contractHeap((uint32_t)header - heap->start_address, heap);

        if( ( (header->size - (old_length - new_length)) > 0)){
            header->size -= old_length - new_length;
            footer = (footer_t*)((uint32_t)header + header->size - sizeof(footer_t));

            footer->magic = KHEAP_MAGIC;
            footer->header_ref = header;
        } else {
            uint32_t iterator = 0;
            
            while( (iterator < heap->index.size) && (lookupItemInOrderedArray(iterator, &heap->index) != (void*)test_header)){
                iterator++;    
            }
            if(iterator < heap->index.size){
                removeItemInOrderedArray(iterator, &heap->index);
            }
        }
    }

    if(do_add == 1){
        insertOrderedArray((void*) header, &heap->index);
    }

}

static uint8_t headerLessThanComparison(void* a, void* b){
    return ( ((header_t*)a)->size < ((header_t*)b)->size ) ? 1 : 0;
}

static int findSmallestHole(uint32_t size, uint8_t page_align, heap_t* heap){
    uint32_t iterator = 0;

    while(iterator < heap->index.size){
        header_t* header = (header_t*) lookupItemInOrderedArray(iterator,&(heap->index));

        if(page_align > 0){
            uint32_t location = (uint32_t)header;
            int offset = 0;

            if( ( (location + sizeof(header_t)) & 0xFFFFF000) != 0 ){
                offset = 0x1000 - (location + sizeof(header_t)) % 0x1000;
            }

            int hole_size = (int) header->size - offset; //header does not count toward hole's size
            if(hole_size >= (int)size ){
                break;
            }

        } else if(header->size >= size){
            break;
        }

        iterator++;
    }

    if(iterator == heap->index.size){ //couldn't find a hole
        return -1;
    } else {
        return iterator;
    }
}


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

    if(kheap != 0){
        terminalWriteString("\nAllocating ");
        terminalPutNumber(size);
        terminalWriteString(" bytes");

        void* addr = allocHeap(size,(uint8_t)isAligned,kheap); //allocate memory based on provided size
        if(physical_address != NULL){
            page_t* page = getPage((uint32_t)addr,DO_NOT_CREATE_PAGE_IF_NONEXISTENT,kernel_directory);
            *physical_address = (page->frame * 0x1000 )+ ((uint32_t)addr &  0xFFF);
        }
        return (uint32_t)addr;
    } else{

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
}


void kfree(void* p){
    freeHeap(p,kheap);
}