#ifndef _FILE_SYSTEM_H
#define _FILE_SYSTEM_H

#include <stddef.h>
#include <stdint.h>

#define MAX_FILE_NAME_LENGTH 128


//typedefs

typedef struct fs_node fs_node_t;

typedef uint32_t (*read_type_t)(fs_node_t*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(fs_node_t*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(fs_node_t*);
typedef void (*close_type_t)(fs_node_t*);
typedef struct dirent* (*readdir_type_t)(fs_node_t*,uint32_t);
typedef struct fs_node_t* (*finddir_type_t)(fs_node_t*,char *name); 

//struct defintions

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


#endif