PROJECT_LOCATION="/home/kuritofu/projects/ChrisOS"
SCRIPT_FOLDER_LOCATION="$PROJECT_LOCATION/scripts"
BIN_FOLDER_LOCATION="$PROJECT_LOCATION/bin"

$SCRIPT_FOLDER_LOCATION/compileKernel.sh $PROJECT_LOCATION/src/ $BIN_FOLDER_LOCATION/kernel
if [ $? -eq 0 ] ; then
    printf "Compiled kernel.\n"
else 
    exit
fi

$SCRIPT_FOLDER_LOCATION/linkOS.sh
if [ $? -eq 0 ]; then
    printf "Linked OS files.\n"
else 
    exit
fi

$SCRIPT_FOLDER_LOCATION/createImage.sh
if [ $? -eq 0 ]; then
    printf "Created OS image.\n"
else 
    exit
fi

printf "\nDone.\n"