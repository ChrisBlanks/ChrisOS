#include <kernel/serial_logger.h>
#include <kernel/serial.h>


uint32_t LOGGER_COM_PORT = 0x0;

uint32_t com_port_address_map[] = { 0, COM1_ADDRESS, COM2_ADDRESS, COM3_ADDRESS, COM4_ADDRESS};


void initializeLogger(uint32_t com_port){
    if(com_port <= 0 || com_port > MAX_COM_PORT_NUM){
        return;
    }

    LOGGER_COM_PORT = com_port_address_map[com_port];

    writeSerialString(LOGGER_COM_PORT,"--- Serial Logger Output ---" "\n");
}


void changeCOMPort(uint32_t new_port){
    if(new_port <= 0 || new_port > MAX_COM_PORT_NUM){
        return;
    }

    LOGGER_COM_PORT = com_port_address_map[new_port];
}


void logGeneralInfo(char* message){
    writeSerialString(LOGGER_COM_PORT,"Info: ");
    writeSerialString(LOGGER_COM_PORT, message);
    writeSerialString(LOGGER_COM_PORT,"\n");
}

void logDebugInfo(char* message){
    writeSerialString(LOGGER_COM_PORT,"Debug: ");
    writeSerialString(LOGGER_COM_PORT, message);
    writeSerialString(LOGGER_COM_PORT,"\n");
}

void logError(char* error_message){
    writeSerialString(LOGGER_COM_PORT,"Error: ");
    writeSerialString(LOGGER_COM_PORT, error_message);
    writeSerialString(LOGGER_COM_PORT,"\n");
}
