#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/kernelito.kernel isodir/boot/kernelito.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "kernelito" {
	multiboot /boot/kernelito.kernel
}
EOF
grub-mkrescue -o kernelito.iso isodir
