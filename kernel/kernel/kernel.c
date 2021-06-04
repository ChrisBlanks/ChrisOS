#include <stdio.h>

#include <kernel/tty.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>

void displayOSDetails(){
    //To-Do: Implement number formatting in printf
    //uint16_t cursor_pos = cursorPosition();
    //printf("Current cursor pos: %d",cursor_pos);
    printf("\n---  Operating System Details ---\n");
    printf("OS Name: ChrisOS\n");
    printf("OS Creator: Chris Blanks\n");
    printf("OS Architecture: i686\n\n");
    //cursor_pos = cursorPosition();
    //printf("Current cursor pos: %d",cursor_pos);
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
    asm volatile ("int $0x04");
}

void secondTest(int test){
    terminalPutNumber(test);
}


//Kernel Entry Point
void kernel_main(void){
    initGDT();
    initIDT();
    
    terminalInitialize();

    displayOSName();
    displayOSDetails();

    printf("Interrupt test\n");
    testRaisingInterrupts();
    printf("Raised interrupts\n");

    /*
    printf("Interrupt test");
    int test = 5;
    test = test /0;
    secondTest(test);
    //testRaisingInterrupts();
    printf("Raised interrupts");
    */
    return;
}


