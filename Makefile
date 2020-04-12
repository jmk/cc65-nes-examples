
CC := cc65
CA := ca65
LD := ld65

TARGETS := example1.nes
TARGETS += example2.nes
TARGETS += example3.nes
TARGETS += example4.nes
TARGETS += example5.nes

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

clean:
	@rm -fv $(TARGETS)
	@rm -fv $(OBJECTS)
	@rm -fv $(ASSEMBLY_SOURCES)

%.s: %.c
	$(CC) -Oi $< --add-source

%.o: %.s
	$(CA) $<

%.nes: %.o crt0.o
	$(LD) -C nes.cfg -o $@ crt0.o $< nes.lib
