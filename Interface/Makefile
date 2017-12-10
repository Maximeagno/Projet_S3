# Makefile
CC=gcc -fsanitize=address

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
LDLIBS= `pkg-config --libs sdl` `pkg-config --libs gtk+-3.0` -lSDL_image
LDFLAGS= $(PTHREAD) $(GTKLIB) -export-dynamic

SRC= interface.c ../Preprocess/pixel-from-image.c  ../Preprocess/pretraitement.c ../Preprocess/text_blocks_detection.c ../Preprocess/binarization.c ../Preprocess/mainFunctions.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: interface

interface: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ interface

-include ${DEP}

# END
