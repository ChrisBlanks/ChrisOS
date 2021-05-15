SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi

# all compiler (gcc) options used explanation:
# -02              -> gcc performs nearly all supported optimizations to increase performance
# -g               -> Tells the compiler to emit extra information for use by a debugger
# --sysroot=dir    -> use 'dir' as the logical root directory for headers & libraries 
# -isystem=dir     -> adds 'dir' to the list of directories to be searched for header files during preprocessing
# -ffreestanding   -> assert that compilation targets a freestanding environment (no standard library & program startup not at regular "main")
# -Wall            -> enables "all" warning flags (some are not included)
# -Wextra          -> enables some extra warning flags that are not enabled by '-Wall'
# -nostdlib        -> indicates to not use the standard system startup files or libraries when linking (certain options are ignored)
# -lgcc            -> specifies to use internal gcc library subroutines
# -lk              -> link this project's kernel static library (libk.a)    
# -std=gnu11       -> use the gnu11 C standard for compiling
# -o value         -> name output file as value.o  
# -c               -> compile or assemble, but not link
# -MD              -> equivalent to '-M -MF file', where file is equal to what '-o' is set to. Generates a dependency output file that 'make' can process.
#                  -> The generated file has a '.d' extension. The '-E' option is not implied, so the compiling process is not impeded.
# -T script        -> use 'script' as a the linker script
# -print-file-name -> print the full absolute name of the library file passes as an argument. Nothing else is done (no compiling or linking)

# all archive (ar) options used explanation:
#  r ->  insert files into archive w/ replacement if they already exist
#  c ->  create the archive file
#  s ->  write an object file index into the archive (or update an existing one)

