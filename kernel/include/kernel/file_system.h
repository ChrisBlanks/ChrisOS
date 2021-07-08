#ifndef _FILE_SYSTEM_H
#define _FILE_SYSTEM_H

#include <stddef.h>
#include <stdint.h>

#define MAX_FILE_NAME_LENGTH 128

///node flags definitions
#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
//skipped 0x07 to allow FS_MOUNTPOINT to be OR'd w/ FS_DIRECTORY
#define FS_MOUNTPOINT  0x08  

///typedefs

typedef struct fs_node fs_node_t;
typedef struct dirent dirent_t;

typedef uint32_t (*read_type_t)(fs_node_t*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(fs_node_t*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(fs_node_t*,uint8_t,uint8_t write);
typedef void (*close_type_t)(fs_node_t*);
typedef dirent_t* (*readdir_type_t)(fs_node_t*,uint32_t);
typedef fs_node_t* (*finddir_type_t)(fs_node_t*,char *name); 


///struct defintions
struct fs_node {
    char file_name[MAX_FILE_NAME_LENGTH];

    uint32_t flags;        //node type
    uint32_t perm_mask;    //permission mask
    uint32_t uid;          //user id of owner
    uint32_t guid;         //group id
    uint32_t inode;        //device specific unique id for node
    uint32_t length;       //size of file in bytes
    uint32_t impl;         //implementation specific value    

    // function pointers for node 
    read_type_t read;         //called when reading from node content
    write_type_t write;       //called when writing to node content
    open_type_t open;         //called when a node is opened as a file descriptor
    close_type_t close;       //called when a node is closed
    readdir_type_t readdir;   //called when reading child nodes of a directory node
    finddir_type_t finddir;   //called when searching for child node

    fs_node_t* ptr;        //pointer used for symlinks & mountpoints
    
};

struct dirent { //returned by readdir call 
   char file_name[128]; 
   uint32_t inode;  //inode number
};


///extern variables
extern fs_node_t* fs_root; //file system root node

///function declarations
uint32_t readFs(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer);
uint32_t writeFs(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer);
void openFs(fs_node_t* node, uint8_t read, uint8_t write);
void closeFs(fs_node_t* node);

dirent_t* readDirFs(fs_node_t* node, uint32_t index);
fs_node_t* findDirFs(fs_node_t* node, char* name);

#endif