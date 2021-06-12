#ifndef _FRAME_H_
#define _FRAME_H_

#include <stddef.h>
#include <stdint.h>

#include <kernel/paging.h>

#define IS_KERNEL 1
#define IS_WRITEABLE 1

//macros for selecting a frame
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

extern uint32_t* frames;
extern uint32_t numFrames;

void allocFrame(page_t* page, int isKernel, int isWriteable);
void freeFrame();

#endif