
BUILDOPTS  = -std=c++11 -g
BUILDOPTS += -Wall -Wextra -Werror -Wno-unused-parameter
CC=g++
CC+=${BUILDOPTS}

SRC_DIR   = ./src
SRC       = $(wildcard ${SRC_DIR}/*.c) $(wildcard ${SRC_DIR}/**/*.c)
OBJ       = $(SRC:.c=.o)
MAIN      = ${SRC_DIR}/main.c
INCLUDE   = -I$(SRC_DIR:./=)

BIN       = ./hayashi.out

CFG       = ~/.hayashi
CFG_FILE  = ${CFG}/.hayashi
PKG       = ${PWD}/pkg
CFG_PKG   = ${CFG}/pkg/
CFG_CORE  = ${CFG}/pkg/core/
CFG_REPO  = ${CFG}/repo/

all: ${BIN}

${BIN}: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< ${INCLUDE}

multi:
	make -j6 $(OBJ)
	make -j6

test: ${BIN}
	${BIN} show some_pkg
	${BIN} add some_pkg --force

clean:
	rm -rf $(BIN) $(OBJ)

restart: clean ${BIN}

install: ${BIN}
	cp ${BIN} /usr/bin/hayashi -f

stats: ${SRC_DIR}
	wc --lines ${SRC_DIR}/**/*.*

${CFG}:
	mkdir ${CFG}

${CFG_FILE}: ${CFG}
	touch ${CFG_FILE}

${CFG_PKG}: ${CFG}
	mkdir ${CFG_PKG}
	mkdir ${CFG_PKG}/custom/

${CFG_CORE}: ${CFG_PKG}
	git submodule update --init pkg
	ln -s ${PKG} ${CFG_CORE}

${CFG_REPO}:
	mkdir ${CFG_REPO}

config: ${CFG_FILE} ${CFG_PKG} ${CFG_REPO} ${CFG_CORE}

.PHONY: multi test clean restart install stats config
