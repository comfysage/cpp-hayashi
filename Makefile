
BUILDOPTS  = -std=c++11 -g
BUILDOPTS += -Wall -Wextra -Werror -Wno-unused-parameter
CC=g++
CC+=${BUILDOPTS}

SRC_DIR   = ./src
SRC       = $(wildcard ${SRC_DIR}/*.c) $(wildcard ${SRC_DIR}/**/*.c)
OBJ       = $(SRC:.c=.o)
MAIN      = ${SRC_DIR}/main.c
INCLUDE   = -I$(SRC_DIR:./=)

NAME      = hayashi
BIN       = ./${NAME}.out

CFG       = ~/.${NAME}
CFG_FILE  = ${CFG}/.${NAME}
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
	@echo "\033[01;35m$$\033[0m ${NAME} show some_pkg"
	@${BIN} show some_pkg
	@echo "\033[01;35m$$\033[0m ${NAME} add some_pkg"
	@${BIN} add some_pkg --force
	@echo "\033[01;35m$$\033[0m ${NAME} update some_pkg"
	@${BIN} update some_pkg

clean:
	rm -rf $(BIN) $(OBJ)

restart: clean ${BIN}

install: ${BIN}
	cp ${BIN} /usr/bin/${NAME} -f

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
