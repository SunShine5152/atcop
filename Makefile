DIR_INC = ./
DIR_SRC = ./
DIR_OBJ = ./
DIR_BIN = ./
#DIR_INC = ./include
#DIR_SRC = ./src
#DIR_OBJ = ./obj
#DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

#$(info "start")
#$(info $(DIR_OBJ))
#$(warning $(DIR_BIN))
#$(warning "start")
#$(error "start")

TARGET = main
BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall -I${DIR_INC} -I/usr/include/lua5.1/

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@ -lm -llua5.1
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean

clean:
	rm *.o
	rm main
