#ifndef _SERIAL_LOGGER_H
#define _SERIAL_LOGGER_H

#include <stddef.h>
#include <stdint.h>


typedef enum COM_PORTS{
    COM1 = 1,
    COM2 = 2,
    COM3 = 3,
    COM4 = 4
} COM_PORTS;



void initializeLogger(uint32_t com_port);

void changeCOMPort(uint32_t new_port);

void logGeneralInfo(char* message);
void logDebugInfo(char* message);
void logError(char* error_message);

#endif