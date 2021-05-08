#!/bin/bash

SCRIPT_NAME=`basename "$0"`

#config variables
PROJECT_LOCATION="/home/kuritofu/projects/ChrisOS"
BIN_DIR="$PROJECT_LOCATION/bin"

OS_NAME="ChrisOS"
OS_FILE="$OS_NAME.bin"
OS_FILE_LOCATION="$BIN_DIR/$OS_FILE"

GRUB_FILE_NAME="grub.cfg"
GRUB_CONFIG_LOCATION="$PROJECT_LOCATION/$GRUB_FILE_NAME"

ISO_DIR_NAME="isodir"
ISO_DIR_LOCATION="$BIN_DIR/$ISO_DIR_NAME"
BOOT_DIR_LOCATION="$ISO_DIR_LOCATION/boot"
GRUB_DIR_LOCATION="$BOOT_DIR_LOCATION/grub"

OUTPUT_FILE="$BIN_DIR/$OS_NAME.iso"


printf "Running $SCRIPT_NAME...\n\n"

if [ ! -d $ISO_DIR_LOCATION ]; then
    printf "Creating ISO directory.\n"
    mkdir $ISO_DIR_LOCATION
fi

if [ ! -d $BOOT_DIR_LOCATION ]; then
    printf "Creating boot directory.\n"
    mkdir $BOOT_DIR_LOCATION
fi

if [ ! -d $GRUB_DIR_LOCATION ]; then
    printf "Creating grub directory.\n"
    mkdir $GRUB_DIR_LOCATION
fi

cp $OS_FILE_LOCATION $BOOT_DIR_LOCATION/$OS_FILE
cp $GRUB_CONFIG_LOCATION $GRUB_DIR_LOCATION/$GRUB_FILE_NAME

grub-mkrescue -o $OUTPUT_FILE $ISO_DIR_LOCATION