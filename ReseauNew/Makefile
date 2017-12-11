CC=gcc -fsanitize=address

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image

SRC= mainRes.c link.c class.c test.c alphabet.c add.c ../../amelie.bertin/Preprocess/mainFunctions.c ../../amelie.bertin/Preprocess/pixel-from-image.c ../../amelie.bertin/Preprocess/pretraitement.c ../../amelie.bertin/Preprocess/text_blocks_detection.c ../../amelie.bertin/Preprocess/binarization.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: mainRes

mainRes: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} mainRes

-include ${DEP}

# END

