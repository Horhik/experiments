-include config.mk


CC = cc
CFLAGS = -std=c89 -Wall -Wextra -pedantic -Os
LDLIBS =


BINS = \
	sdl \


all: ${BINS}

CFLAGS.sdl = ${SDL_CFLAGS}
LDLIBS.sdl = ${SDL_LDLIBS}


CFLAGS.sdl_win = ${SDL_CFLAGS}
LDLIBS.sdl_win = ${SDL_LDLIBS}


.c:
	echo "${CC} ${CFLAGS} ${CFLAGS.$@} -o $@ $< ${LDLIBS} ${LDLIBS.$@}"
	${CC} ${CFLAGS} ${CFLAGS.$@} -o $@ $< ${LDLIBS} ${LDLIBS.$@}


clean:
	rm -f ${BINS} *.o


.PHONY: all clean
