#include <stdio.h>

#include <kernel/tty.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>

#include <kernel/timer.h>
#include <kernel/keyboard.h>
#include <kernel/paging.h>
#include <kernel/kheap.h>
#include <kernel/serial.h>


void displayOSDetails(){
    printf("\n---  Operating System Details ---\n");
    printf("OS Name: ChrisOS\n");
    printf("OS Creator: Chris Blanks\n");
    printf("OS Architecture: i686\n\n");

}

void displayOSName(){
    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

   printf(ascii_art);    
}

void testRaisingInterrupts(){
    //asm volatile ("int $0x03");
    //asm volatile ("int $0x04");
    asm volatile ("int $0x0E");
}

void secondTest(int test){
    terminalPutNumber(test);
}


//Kernel Entry Point
void kernel_main(void){
    initGDT();
    initIDT();
    
    terminalInitialize();
    initTimer(DEFAULT_TIMER_FREQ);
    initKeyboard();
    initSerialComms();

    displayOSName();
    displayOSDetails();

    initializePaging();

    writeSerialString(COM1,"This is my debug message\n");

    //loop forever 
    for(;;){
        asm("hlt");
    }
    
    return;
}


