SCRIPT_NAME=`basename "$0"`
CMD_FORMAT="SCRIPT_NAME path/to/file"
NUM_OF_ARGS=1

printf "Running $SCRIPT_NAME...\n\n"

if [ "$#" -ne $NUM_OF_ARGS  ]; then
    printf "Illegal number of arguments. Num: {$#}\n"
    printf "Command Format: $CMD_FORMAT\n\n"

    exit
fi

FILE_TO_CHECK=$1

if grub-file --is-x86-multiboot $FILE_TO_CHECK; then
    printf "multiboot confirmed for $FILE_TO_CHECK\n\n"
else
    printf "multiboot is not confirmed for $FILE_TO_CHECK\n\n"
fi