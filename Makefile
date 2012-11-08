TOP_DIR := $(shell pwd)
HEAD_DIR := $(TOP_DIR)/arch/arm

CROSS_COMPILE = arm-maxwit-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -ffreestanding -nostdinc -nostdlib -fno-builtin -I$(TOP_DIR)/include -O2 -Wall -Werror -mno-thumb-interwork

src   = $(shell find ./ -name "*.c") 
#objs = core/delay.o nand/nand_core.o soc_init.o nand/my_nand.o
objs = $(patsubst %.c,%.o,$(src))

all: bl1.bin bl1.dis
	@echo

bl1.bin: bl1.elf
	$(OBJCOPY) -O binary -S $< $@

bl1.dis: bl1.elf
	$(OBJDUMP) -D $< > $@

bl1.elf: $(HEAD_DIR)/head.o $(objs)
	$(LD) -T $(HEAD_DIR)/bl1.lds -Ttext 0x402007f8 $^ -o $@

head.o: $(HEAD_DIR)/head.S
	$(AS) -o $@ $<

$(objs):%.o:%.c
	$(CC) $(CFLAGS) -include ./arm/omap3.h -c $< -o $@

#delay.o: core/delay.c  
#	$(CC) $(CFLAGS) -include ./arm/omap3.h -c $< -o $@
#
#nand_core.o: nand/nand_core.c 
#	$(CC) $(CFLAGS) -include ./arm/omap3.h -c $< -o $@
#
#my_nand.o: nand/my_nand.c 
#	$(CC) $(CFLAGS) -include ./arm/omap3.h -c $< -o $@

clean:
	@rm -vf $(HEAD_DIR)/*.o bl1.bin bl1.elf bl1.dis $(objs)

