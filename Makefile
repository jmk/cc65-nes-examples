.PHONY: clean all

.PRECIOUS: *.o

all: example1.nes example2.nes example3.nes example4.nes example5.nes

clean:
	@rm -fv example1.s example2.s example3.s example4.s example5.s
	@rm -fv example1.o example2.o example3.o example4.o example5.o
	@rm -fv example1.nes example2.nes example3.nes example4.nes example5.nes
	@rm -fv crt0.o

crt0.o: crt0.s
	ca65 crt0.s

%.o: %.c
	cc65 -Oi $< --add-source
	ca65 $*.s
	rm $*.s

%.nes: %.o crt0.o
	ld65 -C nes.cfg -o $@ crt0.o $< nes.lib
