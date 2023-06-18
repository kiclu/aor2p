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

SIGNAL_CHAIN = -as=16 -gs -o=output.bmp

SIGNAL_CHAIN_LOAD = -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 \
-a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -a=1 -s=1 -o=output_load.bmp

SIGNAL_CHAIN_LOAD_GS = -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs \
-gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs \
-gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -gs -o=output_load_gs.bmp

CFLAGS  = -Wall -O2 -Wno-sequence-point -Iinclude -Ilib -march=native

SOURCES = $(shell find . -name "*.c" -printf "%P ")
vpath %.c $(sort $(dir ${SOURCES}))

all:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm

run_s3:
	./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN}

run_s0:
	./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN}

run_s2:
	./aor2p res/gouldian_finch.bmp --no-pipeline ${SIGNAL_CHAIN}

run_s3_stress:
	./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN_LOAD}

run_s0_stress:
	./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN_LOAD}

run_s2_stress:
	./aor2p res/gouldian_finch.bmp --no-pipeline ${SIGNAL_CHAIN_LOAD}

run_s3_stress_gs:
	./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN_LOAD_GS}

run_s0_stress_gs:
	./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN_LOAD_GS}

run_s2_stress_gs:
	./aor2p res/gouldian_finch.bmp --no-pipeline ${SIGNAL_CHAIN_LOAD_GS}

debug:
	gdb --args ./aor2p res/gouldian_finch.bmp --no-pipeline --no-simd ${SIGNAL_CHAIN_LOAD}

valgrind:
	valgrind --leak-check=full --track-origins=yes ./aor2p res/gouldian_finch.bmp ${SIGNAL_CHAIN}

clean:
	rm -f ${TARGET}
	rm -f *.bmp
	rm -f *.jpg

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(wildcard ${DIR_BUILD}/*.d)
