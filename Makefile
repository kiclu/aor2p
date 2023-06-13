DIR_BUILD = build
DIR_LIBS  = lib
DIR_INC   = include
DIR_SRC   = src

TARGET 	  = aor2p

AS      = ${TOOLPREFIX}as
CC      = ${TOOLPREFIX}gcc
CXX     = ${TOOLPREFIX}g++
LD      = ${TOOLPREFIX}ld
OBJCOPY = ${TOOLPREFIX}objcopy
OBJDUMP = ${TOOLPREFIX}objdump

SIGNAL_CHAIN = -as=10 -as=10 -gs -as=10 -as=10 -as=10 -s=30 -a=10 -a=10 -o=output.bmp

SIGNAL_CHAIN_LOAD = -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -o=output_load.bmp

CFLAGS  = -Wall -O3 -Wno-sequence-point -Iinclude -Ilib -march=native

SOURCES = $(shell find . -name "*.c" -printf "%P ")
vpath %.c $(sort $(dir ${SOURCES}))

all:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES}

run_opt:
	./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN}

run_nsnp:
	./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN}

run_np:
	./aor2p res/gouldian_finch.bmp --no-pipeline ${SIGNAL_CHAIN}

run_opt_stress:
	./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN_LOAD}

run_nsnp_stress:
	./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN_LOAD}

run_np_stress:
	./aor2p res/gouldian_finch.bmp --no-pipeline ${SIGNAL_CHAIN_LOAD}

debug:
	gdb --args ./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN_LOAD}

valgrind:
	valgrind --leak-check=full --track-origins=yes ./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN}

clean:
	rm -f ${TARGET}

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(wildcard ${DIR_BUILD}/*.d)
