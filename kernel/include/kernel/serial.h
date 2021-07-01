#ifndef _SERIAL_H
#define _SERIAL_H

#include <stddef.h>
#include <stdint.h>


///com port addresses
// IRQ #4 for ports 1 & 3; IRQ #3 for ports 2 & 4
#define COM1_ADDRESS 0x3F8
#define COM2_ADDRESS 0x2F8
#define COM3_ADDRESS 0x3E8
#define COM4_ADDRESS 0x2F8

#define MAX_COM_PORT_NUM 4

///com port offsets
#define DATA_REG_OFFSET             0
#define INTERRUPT_ENABLE_OFFSET     1

//only true when Divisor Latch Access Bit (DLAB) is set
#define BAUD_DIVISOR_LSB_OFFSET     0
#define BAUD_DIVISOR_MSB_OFFSET     1

#define INTERRUPT_AND_FIFO_CONTROL_OFFSET    2
#define LINE_CONTROL_REG_OFFSET              3
#define MODEM_CONTROL_REG_OFFSET             4
#define LINE_STATUS_REG_OFFSET               5
#define MODEM_STATUS_REG_OFFSET              6
#define SCRATCH_REG_OFFSET                   7


///mode flags
#define MODE_5_DATA_BITS 0x0
#define MODE_6_DATA_BITS 0x1
#define MODE_7_DATA_BITS 0x2
#define MODE_8_DATA_BITS 0x3

#define MODE_1_STOP_BIT         0x0 << 2
#define MODE_MULTIPLE_STOP_BITS 0x1 << 2 

#define MODE_NONE_PARITY_BIT   0x0 << 3
#define MODE_ODD_PARITY_BIT    0x1 << 3
#define MODE_EVEN_PARITY_BIT   0x3 << 3
#define MODE_MARK_PARITY_BIT   0x5 << 3
#define MODE_SPACE_PARITY_BIT  0x7 << 3



///Baud Rates (how quickly serial line switches states
// baud rate =/= bps
#define MAX_SERIAL_BAUD_RATE  115200
#define DEFAULT_BAUD_RATE     38400

#define BAUD_RATE_9600    9600
#define BAUD_RATE_38400   DEFAULT_BAUD_RATE
#define BAUD_RATE_115200  MAX_SERIAL_BAUD_RATE


///functions
uint32_t initSerialComms();

uint8_t setupCOMPortDefaults(uint32_t  port_address);
uint8_t setupCOMPort(uint32_t  port_address, uint32_t baud_rate,uint32_t mode_flags);

void updateSerialBaudRate(uint32_t  port_address, uint32_t baud_rate);
void updateSerialPortMode(uint32_t  port_address, uint32_t mode_flags);

char receiveSerialData(uint32_t  port_address);
void writeSerialData(uint32_t  port_address, char data);
void writeSerialString(uint32_t  port_address, char* string);

#endif