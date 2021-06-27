#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom ChrisOS.iso -serial file:serial.log
