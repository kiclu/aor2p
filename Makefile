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

SIGNAL_CHAIN = -l -p=2 -m=2 -gs -as=128 --neg -l -p=2 -m=2 -gs -as=128 --neg -o=output.bmp
SIGNAL_CHAIN2 = -l -p=2 -m=2 -as=100 -d=2 -gs -o=output.bmp

IMG_SOURCE = res/gouldian_finch.bmp

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
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm -pthread -DSIMDIP_VERBOSE

all_pt2:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm -pthread -DSIMDIP_VERBOSE -DTHREAD_COUNT=2

all_pt4:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm -pthread -DSIMDIP_VERBOSE -DTHREAD_COUNT=4

all_pt8:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm -pthread -DSIMDIP_VERBOSE -DTHREAD_COUNT=8

all_pt32:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES} -lm -pthread -DSIMDIP_VERBOSE -DTHREAD_COUNT=32

run_s0:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN} -s0

run_s2:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN} -s2

run_s3:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN} -s3


run_s0_stress:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD} -s0

run_s2_stress:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD} -s2

run_s3_stress:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD} -s3


run_s0_stress_gs:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD_GS} -s0

run_s2_stress_gs:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD_GS} -s2

run_s3_stress_gs:
	./aor2p ${IMG_SOURCE} ${SIGNAL_CHAIN_LOAD_GS} -s3

clean:
	rm -f ${TARGET}
	rm -f *.bmp
	rm -f *.jpg
	rm -f *.png

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(wildcard ${DIR_BUILD}/*.d)
