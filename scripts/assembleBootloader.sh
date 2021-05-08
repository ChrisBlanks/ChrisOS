#!/bin/bash

SCRIPT_NAME=`basename "$0"`
CMD_FORMAT="SCRIPT_NAME bootloader/file/path output/directory/path"
BOOTLOADER_EXTENSION=".s"
NUM_OF_ARGS=2

printf "Running $SCRIPT_NAME...\n\n"

if [ "$#" -ne $NUM_OF_ARGS  ]; then
    printf "Illegal number of arguments. Num: {$#}\n"
    printf "Command Format: $CMD_FORMAT\n\n"

    exit
fi

BOOTLOADER_PATH=$1
OUTPUT_DIR_PATH=$2
FILE_NAME=`basename $1 $BOOTLOADER_EXTENSION`

$HOME/opt/cross/bin/i686-elf-as $BOOTLOADER_PATH -o $OUTPUT_DIR_PATH/$FILE_NAME.o
