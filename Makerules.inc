CC   = clang
CXX  = clang++
LD   = ld.lld
AS   = yasm -parser=gas
MAKE = bmake	# This is really for me, but you can comment it out.

ARCH = x86_64
TRIPLE = $(ARCH)-unknown-none-gnu

CSTD = -std=c11 -Wall -Werror -Wconversion	##Embed these here so we don't forget.
C_REQUIREDFLAGS := -Werror -O2 -ffreestanding -mno-red-zone -mcmodel=kernel -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -mno-mmx -target $(TRIPLE) $(CPU_TUNING)
AS_FLAGS = -felf64

CPU_TUNING = -mtune=znver1
CPU_EXCLUSIVE = -march=znver1


