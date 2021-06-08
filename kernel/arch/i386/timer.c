#include "isr.h"
#include "utility.h"
#include <kernel/tty.h>

#include <kernel/timer.h>

uint32_t tick = 0;
uint32_t currentFrequency = 0;
uint32_t seconds = 0;

static void timerCallback(registers_t regs){
    tick++; 

    if(tick % currentFrequency == 0){
        seconds++;
        terminalWriteString("Seconds passed: ");
        terminalPutNumber(seconds);
        terminalWriteString("\n"); 
    }

}


uint32_t getCurrentFrequency(){
    return currentFrequency;
}

uint32_t getCurrentTick(){
    return tick;
}

void initTimer(uint32_t freq) {
    uint32_t divisor;
    uint8_t low_byte, high_byte;

    currentFrequency = freq; //store current frequency

    registerInterruptHandler(IRQ0, &timerCallback); //register timer callback to IRQ0

    divisor = INPUT_CLOCK_CONSTANT / freq;

    outb(0x43,0x36); //send command byte

    //send divisor in bytes
    low_byte = (uint8_t) (divisor & 0xFF);
    high_byte = (uint8_t) ( (divisor >> 8) & 0xFF);

    outb(0x40,low_byte);
    outb(0x40,high_byte);


}


void updateTimerFrequency(uint32_t freq){
    uint32_t divisor = INPUT_CLOCK_CONSTANT / freq;

    outb(0x43,0x36); //send command byte

    //send divisor in bytes
    uint8_t low_byte = (uint8_t) (divisor & 0xFF);
    uint8_t high_byte = (uint8_t) ( (divisor >> 8) & 0xFF);

    outb(0x40,low_byte);
    outb(0x40,high_byte);
    
    currentFrequency = freq; //store current frequency
}


void wait(uint32_t wait_ticks){
    uint64_t tickBound = wait_ticks + tick;

    while(tick < tickBound){} //wait until current tick exceeds bound before exiting

}