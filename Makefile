OBJECTS = boot.o kernel.o console.o
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./include -c
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
AS = i686-elf-as
ASFLAGS = 

all: hobbyos.bin

hobbyos.bin: $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o hobbyos.bin

iso: hobbyos.bin
	mkdir -p isodir/boot/grub 
	cp hobbyos.bin isodir/boot/hobbyos.bin 
	cp grub.cfg isodir/boot/grub/grub.cfg 
	grub-mkrescue -o hobbyOS.iso isodir
	rm -rf isodir

run: all
	qemu-system-i386 -kernel hobbyos.bin

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o hobbyos.bin hobbyOS.iso isodir

	
