CC = cc
CFLAGS = -std=c++17
LDFLAGS = -lstdc++ -lm
PREFIX = /usr/local

SRC = main.cpp elostore.cpp
OBJ = ${SRC:.cpp=.o}

all: elocalc

elocalc: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

%.o: %.cpp
	${CC} -c ${CFLAGS} $<

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f elocalc ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/elocalc

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/elocalc

clean:
	rm -f elocalc ${OBJ}

.PHONY: all install uninstall clean
