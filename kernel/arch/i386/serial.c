#include <kernel/serial.h>
#include <kernel/isr.h>

#include "utility.h"


//static function prototypes
static uint8_t checkForSerialData(uint32_t  port_address);
static uint8_t isTransmitBufferEmpty(uint32_t  port_address);

static void serialCommsHandler(registers_t regs);


uint32_t initSerialComms(){

    uint8_t com1Result = setupCOMPortDefaults(COM1);

    registerInterruptHandler(IRQ4, &serialCommsHandler); //setup IRQ handler/callback

    return com1Result;
}


uint8_t setupCOMPortDefaults(uint32_t  port_address){
    
    return setupCOMPort( port_address, DEFAULT_BAUD_RATE, MODE_8_DATA_BITS | MODE_1_STOP_BIT| MODE_NONE_PARITY_BIT);
}


uint8_t setupCOMPort(uint32_t  port_address, uint32_t baud_rate,uint32_t mode_flags){
    outb( port_address + INTERRUPT_ENABLE_OFFSET, 0x00); //disable all interrupts
    outb( port_address + LINE_CONTROL_REG_OFFSET, 0x80); //enable DLAB to set baud rate 

    updateSerialBaudRate( port_address, baud_rate);
    updateSerialPortMode(port_address, mode_flags);
    
    outb( port_address + INTERRUPT_AND_FIFO_CONTROL_OFFSET, 0xC7); //enable FIFO, clear contents, and set a 14 byte threshold
    outb( port_address + MODEM_CONTROL_REG_OFFSET, 0x0B); //enable FIFO, clear contents, and set a 14 byte threshold

    outb( port_address + MODEM_CONTROL_REG_OFFSET, 0x1E); //Set in loopback mode to test the serial chip


    //loopback test
    uint8_t test_data = 0xAE;

    outb( port_address + DATA_REG_OFFSET, test_data); //send data
    if( inb( port_address + DATA_REG_OFFSET) != test_data){ //If loopback data is not equal, return 0 (false)
        return 0;
    }

    //disable loopback & enable IRQs; OUT#1 & OUT#2 bits enabled
    outb( port_address+MODEM_CONTROL_REG_OFFSET, 0x0F);

    return 1;
}


char receiveSerialData(uint32_t port_address){
    while( checkForSerialData( port_address) == 0);
    return inb( port_address  + DATA_REG_OFFSET);
}

void writeSerialData(uint32_t port_address, char data){
    while( isTransmitBufferEmpty( port_address) == 0);
    outb( port_address + DATA_REG_OFFSET, data);
}

uint8_t updateSerialBaudRate(uint32_t port_address, uint32_t baud_rate){

    uint32_t divisor = (uint32_t) (MAX_SERIAL_BAUD_RATE / baud_rate);

    outb( port_address + BAUD_DIVISOR_LSB_OFFSET, divisor & 0xFF); //set low byte of baud rate divisor 
    outb( port_address + BAUD_DIVISOR_MSB_OFFSET, (divisor >> 8) & 0xFF); //set high byte of baud rate divisor

}

uint8_t updateSerialPortMode(uint32_t  port_address, uint32_t mode_flags){
    outb( port_address + LINE_CONTROL_REG_OFFSET, mode_flags & 0xFF); //set mode flags
}


static uint8_t checkForSerialData(uint32_t  port_address){
    return inb( port_address + 5) & 0x1;
}

static uint8_t isTransmitBufferEmpty(uint32_t  port_address){
    return inb( port_address + 5) & 0x20;
}


static void serialCommsHandler(registers_t regs){

}