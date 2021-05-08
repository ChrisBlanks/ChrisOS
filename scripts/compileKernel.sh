#!/bin/bash

SCRIPT_NAME=`basename "$0"`
CMD_FORMAT="SCRIPT_NAME source/folder/location output/filename"
NUM_OF_ARGS=2

printf "Running $SCRIPT_NAME...\n\n"

if [ "$#" -ne $NUM_OF_ARGS  ]; then
    printf "Illegal number of arguments. Num: {$#}\n"
    printf "Command Format: $CMD_FORMAT\n\n"

    exit
fi

KERNEL_SRC_LOCATION=$1
KERNEL_OUT_FILE_NAME=$2

if [ ! -d $KERNEL_SRC_LOCATION ]; then
    printf "Kernel source code directory does not exist. Location: {$KERNEL_SRC_LOCATION}\n"
    exit
fi

$HOME/opt/cross/bin/i686-elf-gcc -c $KERNEL_SRC_LOCATION/*.c -o  $KERNEL_OUT_FILE_NAME.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

printf "Done.\n\n"