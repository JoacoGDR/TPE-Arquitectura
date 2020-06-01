include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
ASMSOURCES=$(wildcard [^_]*.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
ASMEXECUTABLE=$(ASMOBJETCS:.o=)


all: $(MODULE)

$(MODULE): $(SOURCES) $(ASMOBJECTS) $(ASMEXECUTABLE)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) $(ASMOBJECTS) -o ../$(MODULE)

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

% : %.o
	$(LD) $(ASMLINKEDITFLAGS) -o $@ $<

clean:
	rm -rf *.o 

.PHONY: all clean print
