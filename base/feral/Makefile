## We need to build the actual kernel before we can be of much use to HAL here...

INCLUDE_PRIVATE = Includepriv



## Include we need...
CFLAGS += $(INCLUDE_PRIVATE) -I$(INCLUDE_EVERYTHING)

all: builddir krnl_o

builddir:
	mkdir build

krnl_o:
	cd krnl && $(MAKE) all && mv krnl.o ../build/krnl.o

