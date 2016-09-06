CC     = gcc
CFLAGS = -std=c99 -ggdb3 -Wall -Wextra

INCDIR = include

SRC1 = src/prog_single.c src/matrix.c

# FIXME find out what is the proper way to call mkdir before building
prog_single:${SRC1}
	@mkdir -p bin
	${CC} ${CFLAGS} -I ${INCDIR} -lgmp -o bin/$@ $^
