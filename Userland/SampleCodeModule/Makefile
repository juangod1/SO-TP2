include Makefile.inc

MODULE=../0000-sampleCodeModule.bin
SOURCES=sampleCodeModule.c stdLib.c stdio.c shell.c mathLib.c plotLib.c contextSwitchDemo.c prodConsProblem.c mmDemo.c
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=_loader.c

LOADEROBJECT=$(LOADERSRC:.c=.o)
STATICLIBS=

all: $(MODULE)

$(MODULE): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o $(MODULE) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(GCC) $(GCCFLAGS) -c $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean
