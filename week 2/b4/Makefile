TARGET		= b4

CC			= avr-gcc
OBJ2HEX		= avr-objcopy
MCU			= atmega128

CFLAGS		= -g -Os -mcall-prologues -mmcu=$(MCU) -Wall -std=c99 -Wstrict-prototypes -Wa,-ahlms=$(TARGET).lst -DF_CPU=8000000
#ASFLAGS	= -Wa,-adhlns=$(<:.S=.lst),-gstabs
LDFLAGS		= -Wl,-Map=$(TARGET).map,--cref -mmcu=$(MCU) -lm -lprintf_min

# Programmer. Ik gebruik avrdude icm crips programmer
PROGRAMMER	= avrdude
PRG_OPTIONS	= -c stk500v2 -P /dev/tty.usbserial-A7005tiJ -p m128 -v

OBJS		= b4.o

# Create all target
all:	$(TARGET).hex

#
# Compile *.c -> *.o
b4.o:	b4.c
	$(CC) $(CFLAGS) -I. -c $<

#		
# Linking all *.o -> *.elf
$(TARGET).elf	:	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET).elf

#
# Create intel hex for download
$(TARGET).hex	:	$(TARGET).elf
	$(OBJ2HEX) -O ihex $(TARGET).elf $(TARGET).hex
		
#
# install
install		:
	$(PROGRAMMER) $(PRG_OPTIONS) -U flash:w:$(TARGET).hex

#
# setconfig
setconfig	:
	$(PROGRAMMER) $(PRG_OPTIONS) -U lfuse:w:0xde:m -U hfuse:w:0xd9:m
	
#
# clean
clean		:
		rm -f *.hex *.o *.obj *.lst *.map *.elf
