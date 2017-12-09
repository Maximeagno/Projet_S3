CC=gcc -fsanitize=address

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= pixel-from-image.c main.c pretraitement.c text_blocks_detection.c binarization.c mainFunctions.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main

-include ${DEP}

# END
