# Makefile for JustForFun Files

# A few variables

CC=gcc
LIBS=-lncurses

SRC_DIR=.
EXE_DIR=./bin

EXES = \
    ./main

${EXE_DIR}/%: %.o
	${CC} -o $@ $< ${LIBS}

%.o: ${SRC_DIR}/%.c
	${CC} -o $@ -c $<

all:    ${EXES}

clean:
	@rm -f ${EXES}