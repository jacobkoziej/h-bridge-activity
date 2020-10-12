# Compiler options
CC=avr-gcc
CFLAGS= -Os -DF_CPU=20000000UL -mmcu=atmega328p

all: task-1.out task-2.out task-3.out

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

%.hex: %.out
	avr-objcopy -O ihex -R .eeprom $< $@

flash.%: %.hex
	avrdude -c usbtiny -p atmega328p -U flash:w:$<:a

clean:
	rm -rvf *.out

.PHONY: flash clean
