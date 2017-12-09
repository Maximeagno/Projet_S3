# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g `pkg-config --cflags gtk+-3.0`
LDLIBS = `pkg-config --libs gtk+-3.0`
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

SRC= interface.c ../../amelie.bertin/ReseauNew/mainRes.c ../../amelie.bertin/class.c ../../amelie.bertin/test.c ../../amelie.bertin/alphabet.c ../../amelie.bertin/add.c ../../amelie.bertin/Preprocess/mainFunctions.c ../../amelie.bertin/Preprocess/pixel-from-image.c ../../amelie.bertin/Preprocess/pretraitement.c ../../amelie.bertin/Preprocess/text_blocks_detection.c ../../amelie.bertin/Preprocess/binarization.c ../Preprocess/main.c
OBJ= ${SRC:.c=.o}
DEP = ${OBJ:.o=.d}

all: main

.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} *~ interface

-include ${DEP}

# END
