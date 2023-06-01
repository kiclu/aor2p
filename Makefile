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

CFLAGS  = -Wall -O3 -Iinclude -Ilib -march=native

SOURCES = $(shell find . -name "*.c" -printf "%P ")
vpath %.c $(sort $(dir ${SOURCES}))

all:
	${CC} -g ${CFLAGS} -o ${TARGET} ${SOURCES}

run:
	./aor2p res/gouldian_finch.bmp output.bmp

debug:
	gdb --args ./aor2p res/gouldian_finch.bmp output.bmp

clean:
	rm -f ${TARGET}

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(wildcard ${DIR_BUILD}/*.d)
