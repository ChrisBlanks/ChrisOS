#!/bin/bash

#config variables
PROJECT_LOCATION="/home/kuritofu/projects/ChrisOS"
BIN_DIR="$PROJECT_LOCATION/bin"

OS_NAME="ChrisOS"

LINKER_FILE="$PROJECT_LOCATION/linker.ld"
BOOT_FILE="$BIN_DIR/boot.o"
KERNEL_FILE="$BIN_DIR/kernel.o"
OUTPUT_FILE="$BIN_DIR/$OS_NAME.bin"

printf "Creating $OS_NAME bin file...\n"
$HOME/opt/cross/bin/i686-elf-gcc -T $LINKER_FILE -o $OUTPUT_FILE -ffreestanding -O2 -nostdlib $BOOT_FILE $KERNEL_FILE -lgcc

if [ $? -eq 0 ] ; then
    printf "No linking issues.\n"
else 
    exit 1
fi

printf "\nDone.\n"