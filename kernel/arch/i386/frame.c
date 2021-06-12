#include "frame.h"
#include "utility.h"


//static functions
static void setFrame(uint32_t frame_addr);
static void clearFrame(uint32_t frame_addr);
static uint32_t testFrame(uint32_t frame_addr);
static uint32_t firstFrame();

//global variables
uint32_t* frames;
uint32_t numFrames;


void allocFrame(page_t* page, int isKernel, int isWriteable){
    if(page->frame != 0){
        return; //frame was already allocated
    } else{
        uint32_t index = firstFrame();
        if(index == (uint32_t)-1){
            panic("No free frames",__FILE__,__LINE__);
        }

        setFrame(index * 0x1000); //set frame bit
        page->present = 1;
        page->rw = (isWriteable) ? 1 : 0;
        page->user = (isKernel) ? 1 : 0;
        page->frame = index;
    }
}


void freeFrame(page_t* page){
    uint32_t frame;

    if(! (frame=page->frame) ){
        return; //no allocated frame, so return
    } else{
        clearFrame(frame);
        page->frame=0x0;
    }
}

//set bit in frames bitset
static void setFrame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000; //calculate frame boundary
    uint32_t index = INDEX_FROM_BIT(frame); //calculate index for frame array
    uint32_t offset = OFFSET_FROM_BIT(frame); //calculate offset by getting remainder

    frames[index] |= (0x1 << offset);
}

//clear bit in frames bitset
static void clearFrame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000; //calculate frame boundary
    uint32_t index = INDEX_FROM_BIT(frame); //calculate index for frame array
    uint32_t offset = OFFSET_FROM_BIT(frame); //calculate offset by getting remainder

    frames[index] &= ~(0x1 << offset); //clear frame bit 
}

//test frame index to see if it is set already
static uint32_t testFrame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000; //calculate frame boundary
    uint32_t index = INDEX_FROM_BIT(frame); //calculate index for frame array
    uint32_t offset = OFFSET_FROM_BIT(frame); //calculate offset by getting remainder

    return (frames[index] & (0x1 << offset));
}

//search for the 1st free frame
static uint32_t firstFrame(){
    uint32_t i, j;

    for(i=0; i < INDEX_FROM_BIT(numFrames); i++){
        if(frames[i] != 0xFFFFFFFF){ // if no frames are free, exit early; otherwise enter logic
            for(j=0; j< 32; j++){ //check every bit for the first open frame
                uint32_t toTest = 0x1 << j;
                if(!(frames[i] & toTest)){
                    return ((i*4*8) + j);
                }
            }
        }
    }

    return (uint32_t)-1; //if no frame is found, return special value
}