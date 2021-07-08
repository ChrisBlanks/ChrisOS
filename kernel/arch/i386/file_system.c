#include <kernel/file_system.h>

//global variables
fs_node_t* fs_root = 0;

///function definitions
uint32_t readFs(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer){
    if(node->read != 0){
        return node->read(node,offset,size,buffer);
    } else{
        return 0;
    }
}

uint32_t writeFs(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer){
    if(node->write != 0){
        return node->write(node,offset,size,buffer);
    } else{
        return 0;
    }
}

void openFs(fs_node_t* node, uint8_t read, uint8_t write){
    if(node->open != 0){
        return node->open(node, read, write);
    } else{
        return;
    }
}

void closeFs(fs_node_t* node){
    if(node->close != 0){
        return node->close(node);
    } else{
        return;
    }
}

dirent_t* readDirFs(fs_node_t* node, uint32_t index){
    if( (node->flags & 0x7) == FS_DIRECTORY && node->readdir != 0){
        return node->readdir(node, index);
    } else{
        return 0;
    }
}

fs_node_t* findDirFs(fs_node_t* node, char* name){
    if( (node->flags & 0x7) == FS_DIRECTORY && node->finddir != 0){
        return node->finddir(node, name);
    } else{
        return 0;
    }
}