GCC = nspire-gcc
LD = nspire-ld
GCCFLAGS = -Os -fdata-sections -ffunction-sections -fomit-frame-pointer -marm -march=armv5te -mtune=arm926ej-s -Wall -W -marm
LDFLAGS =  -nostdlib -Wl,--gc-sections -Wl,--as-needed -flto -lm
OBJCOPY := "$(shell which arm-elf-objcopy 2>/dev/null)"
ifeq (${OBJCOPY},"")
	OBJCOPY := arm-none-eabi-objcopy
endif
EXE = wheresderpy.tns
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
DISTDIR = .
vpath %.tns $(DISTDIR)

all: $(EXE) gen

gen:
	genzehn --input wheresderpy.elf --output derpy.t --compress
	make-prg derpy.t derpy.tns
	rm derpy.t wheresderpy.elf

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

$(EXE): $(OBJS)
	$(LD) $^ -o $(@:.tns=.elf) $(LDFLAGS)
	mkdir -p $(DISTDIR)

clean:
	rm -f *.o *.elf
	rm -f $(DISTDIR)/$(EXE)
