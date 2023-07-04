DIR_BUILD = build
DIR_LIBS  = lib
DIR_INC   = include
DIR_SRC   = src

TARGET 	  = aor2p

AS      = as
CC      = gcc
CXX     = g++
LD      = ld
OBJCOPY = objcopy
OBJDUMP = objdump

CFLAGS  = -Wall -Wpedantic -O3 -Wno-sequence-point -Iinclude -Ilib -march=native
ASFLAGS = 

OBJECTS =

SOURCES_C = $(shell find . -name "*.c" -printf "%P ")
OBJECTS  +=	$(addprefix ${DIR_BUILD}/,${SOURCES_C:.c=.o})
vpath %.c $(sort $(dir ${SOURCES_C}))

SOURCES_S = $(shell find . -name "*.S" -printf "%P ")
OBJECTS  += $(addprefix ${DIR_BUILD}/,${SOURCES_S:.S=.o})
vpath %.S $(sort $(dir ${SOURCES_S}))

all: ${TARGET}

${TARGET}: ${OBJECTS} | ${DIR_BUILD}
	${CC} -o ${TARGET} ${OBJECTS} -lm -pthread

${DIR_BUILD}/%.o: %.s Makefile | ${DIR_BUILD}
	@mkdir -p $(dir ${@})
	${AS} -c ${ASFLAGS} -o ${@} ${<}

${DIR_BUILD}/%.o: %.c Makefile | ${DIR_BUILD}
	@mkdir -p $(dir ${@})
	${CC} -c ${CFLAGS} -W -o ${@} ${<}

${DIR_BUILD}:
	@mkdir ${@}

clean:
	rm -rf ${DIR_BUILD}
	rm -f ${TARGET}

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(wildcard ${DIR_BUILD}/*.d)
