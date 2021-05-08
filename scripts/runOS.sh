#!/bin/bash

SCRIPT_NAME=`basename "$0"`
CMD_FORMAT="SCRIPT_NAME iso/file/path"
NUM_OF_ARGS=1

printf "Running $SCRIPT_NAME...\n\n"

if [ "$#" -ne $NUM_OF_ARGS  ]; then
    printf "Illegal number of arguments. Num: {$#}\n"
    printf "Command Format: $CMD_FORMAT\n\n"

    exit
fi

qemu-system-i386 -cdrom $1