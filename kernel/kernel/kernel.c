#include <stdio.h>

#include <kernel/tty.h>

/*

void renderOSASCIIArt(){
    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

    terminal_color = vgaEntryColor(VGA_COLOR_RED,VGA_COLOR_BLACK);
    terminalWriteString(ascii_art);
}

void renderColorfulASCIIArt(){

    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

    terminalWriteColorful(ascii_art, strlen(ascii_art));

}
*/

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


//Kernel Entry Point
void kernel_main(void){
    terminalInitialize();

    displayOSName();
    displayOSDetails();
    
    return;
}


