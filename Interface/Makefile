# Makefile
CC=gcc

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
LDLIBS= -lm `pkg-config --libs sdl` `pkg-config --libs gtk+-3.0` -lSDL_image
LDFLAGS= $(PTHREAD) $(GTKLIB) -export-dynamic

SRC= interface.c ../Preprocess/pixel-from-image.c  ../Preprocess/pretraitement.c ../Preprocess/text_blocks_detection.c ../Preprocess/binarization.c ../Preprocess/mainFunctions.c ../ReseauNew/link.c ../ReseauNew/alphabet.c ../ReseauNew/add.c ../ReseauNew/class.c ../ReseauNew/test.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: interface

interface: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ interface

-include ${DEP}
# END
