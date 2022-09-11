CC := gcc

FLAGS := -Wall -Wextra -Werror -std=c99
CFLAGS := ${FLAGS} -O3
DFLAGS := ${FLAGS} -g3

SRC := src/*.c
DEST := /usr/local/bin


all: versefetch

versefetch: ${SRC}
	${CC} ${CFLAGS} ${SRC} -o versefetch

debug: ${SRC}
	${CC} ${DFLAGS} ${SRC} -o versefetch

install: versefetch
	mkdir -p ${DEST}
	cp versefetch ${DEST}
	chmod 711 ${DEST}/versefetch

uninstall:
	rm -f ${DEST}/versefetch

clean:
	rm -rf versefetch
