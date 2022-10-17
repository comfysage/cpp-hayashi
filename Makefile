
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

all: ${BIN}

${BIN}: $(OBJ)
	$(CC) -o ${BIN} $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< ${INCLUDE}

run: ${BIN}
	${BIN} add --verbose some_pkg

clean:
	rm -rf $(BIN) $(OBJ)

restart: clean ${BIN}

stats: ${SRC_DIR}
	wc --lines ${SRC_DIR}/**/*.*

.PHONY: run clean restart stats
