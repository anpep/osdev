##
##  system image build rules
##  
##  SPDX-License-Identifier: GPL-2.0-only
##  Copyright (C) 2018, angel
##

-include ../common.mk

platforms = generic
type = custom
size = 256M
target = system.img
grub_target = i386-pc
disk = /dev/loop0

TARGET = /tmp/${target}

all: mount install unmount move

mount:
	$(call verb,allocating ${size} system image)
	${Q}truncate -s ${size} ${TARGET}
	$(call verb,setting up boot partition)
	${Q}losetup ${disk} ${TARGET}
	$(call verb,creating partition table)
	${Q}parted --script ${disk} \
		mklabel msdos \
		mkpart primary 1MiB 31MiB \
		mkpart primary 31MiB 100% \
		set 1 boot on
	$(call verb,creating file systems)
	${Q}mkfs -t ext2 -m 0 -L boot -v ${disk}p1
	${Q}mkfs -t ext2 -m 0 -L data -v ${disk}p2
	$(call verb,mounting boot partition)
	${Q}mkdir -p /tmp/boot
	${Q}mount ${disk}p1 /tmp/boot
	$(call verb,instaling GRUB)
	${Q}mkdir -p /tmp/boot/grub
	${Q}grub-install --no-floppy \
									 --root-directory=/tmp/boot \
									 --target=${grub_target} \
									 ${disk}
	$(call verb,mounting data partition)
	${Q}mkdir -p /tmp/data
	${Q}mount ${disk}p2 /tmp/data

unmount:
	$(call verb,unmount boot partition)
	${Q}umount ${disk}p1
	${Q}rmdir /tmp/boot
	$(call verb,unmount data partition)
	${Q}umount ${disk}p2
	${Q}rmdir /tmp/data
	$(call verb,detaching loop device)
	${Q}losetup -d ${disk}

move:
	$(call verb,moving image file)
	${Q}mv ${TARGET} ${target}

install: ../core/core.elf
	${Q}cp $^ /tmp/boot/boot/
	${Q}cp -R ./boot /tmp/boot

clean:
	${Q}rm -rf ${TARGET} ${target}
	$(call done,cleaned output files)

.PHONY: all clean mount install unmount
