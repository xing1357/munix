CC = /usr/local/bin/i386-elf-gcc
LD = /usr/local/bin/i386-elf-ld
ASM = /usr/local/bin/nasm

INC = ./include
INCLUDE=-I$(INC)
CFG = cfg
OUT = out

SOURCES_C = $(wildcard src/*.c)
SOURCES_ASM = $(wildcard src/asm/*.asm)

OBJ_C = ${SOURCES_C:.c=.o}
OBJ_ASM= ${SOURCES_ASM:.asm=.o}

OBJ = ${OBJ_ASM} ${OBJ_C}
BINARY = $(OUT)/kernel.bin

CFLAGS = $(INCLUDE) -g -nostdlib -ffreestanding -m32 -c -Wall -Wextra
LDFLAGS = -m elf_i386 -T $(CFG)/linker.ld -nostdlib
ASFLAGS = -felf32

all: $(BINARY)

$(BINARY): ${OBJ}
	$(LD) $(LDFLAGS) -o $(BINARY) $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	 $(ASM) $(ASFLAGS) $< -o $@

run: all
	/usr/local/bin/qemu-system-i386 -kernel $(BINARY)

drun: all
	/usr/local/bin/qemu-system-i386 -s -S -kernel $(BINARY)

clean:
	rm -f src/*.o src/asm/*.o $(BINARY)

