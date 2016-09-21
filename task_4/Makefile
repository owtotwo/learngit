ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR)

$(OBJ_DIR)/TodolistConsole.o: $(SRC_DIR)/TodolistConsole.c  $(INC_DIR)/TodolistConsole.h  \
		$(INC_DIR)/TodolistModel.h
	$(CC) $(CC_FLAG) -c $< -o $@
