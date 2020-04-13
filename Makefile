
#CC65_DIR := cc65-nes-2.13.3-1
CC65_DIR := cc65

CC := $(CC65_DIR)/bin/cc65
CA := $(CC65_DIR)/bin/ca65
LD := $(CC65_DIR)/bin/ld65

TARGET_PLATFORM := nes

TARGETS := example1.nes
TARGETS += example2.nes
TARGETS += example3.nes
TARGETS += example4.nes
TARGETS += example5.nes
TARGETS += example6.nes
TARGETS += example7.nes
TARGETS += example8.nes
TARGETS += example9.nes
TARGETS += example10.nes
TARGETS += example11.nes

EMULATOR ?= higan

EXAMPLES := $(TARGETS:..nes=)
OBJECTS := $(TARGETS:.nes=.o)
ASSEMBLY_SOURCES := $(TARGETS:.nes=.s)
C_SOURCES := $(TARGETS:.nes=.c)

.PHONY: all

# Disable builtin rules (for .c, .o) by providing an empty .SUFFIXES rule
# Yes. GNU make is a rat's nest
.SUFFIXES:

# Make sure intermediate files are *NOT* deleted
# Yes. GNU make is a rat's nest
.PRECIOUS: %.s %.o

all: $(TARGETS)

%: %.nes
	$(EMULATOR) $<

clean:
	@rm -fv $(TARGETS)
	@rm -fv $(OBJECTS)
	@rm -fv $(ASSEMBLY_SOURCES)
	@rm -fv crt0.o

%.s: %.c
	$(CC) -Oi $< --target $(TARGET_PLATFORM) -I$(CC65_DIR)/include/ --add-source

%.o: %.s
	$(CA) $<

%.nes: %.o crt0.o
	$(LD) -C nrom_128_horz.cfg -o $@ $^ $(TARGET_PLATFORM).lib

