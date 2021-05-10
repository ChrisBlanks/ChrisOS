#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ChrisOS.kernel isodir/boot/ChrisOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "ChrisOS" {
	multiboot /boot/ChrisOS.kernel
}
EOF
grub-mkrescue -o ChrisOS.iso isodir
