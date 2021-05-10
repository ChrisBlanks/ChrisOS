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


//Kernel Entry Point
void kernel_main(void){
    /*
    char* msg = "Hello, Kernel World!\n" 
                "This will continue on for quite a while," 
                "so that I can get a line break somewhere hahahahahahahahahaha\n";

    char* long_msg = "1This will be a very long message that will hopefully test scrolling\n"
                     "2second line: ffffffffffffffffffffffffffffffffffffffff\n"
                     "3\n"
                     "4\n5ffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                     "\n6a\n7b\n8c\n9d\n10e\n11f\n12g\n13h\n14i\n15j\n16k\n17l\n18m\n19n\n20o\n21p"
                     "fffffffffffffffffffffffffffffffffffffffff"
                     "\n22q\n23r\n24s\n25t\n26ffff\n27after everything";
    */

    char* ascii_art = 
   "  _____ _          _      ____   _____\n"
   " / ____| |        (_)    / __ \\ / ____|\n"
   "| |    | |__  _ __ _ ___| |  | | (___\n"  
   "| |    | '_ \\| '__| / __| |  | |\\___ \n" 
   "| |____| | | | |  | \\__ \\ |__| |____) |\n"
   " \\_____|_| |_|_|  |_|___/\\____/|_____/ \n";

    terminalInitialize();
    printf(ascii_art);
    printf("\nHello, kernel world!");
    
    //renderOSASCIIArt();
    //renderColorfulASCIIArt();
    
    //test output
    //terminalWriteString(msg);
    //terminalWriteString(long_msg);
    
}


