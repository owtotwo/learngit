ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
LIB_DIR = $(ROOT_DIR)/lib

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR) -I$(LIB_DIR)

main: $(OBJ_DIR)/TodolistConsole.o  $(OBJ_DIR)/TodolistService.o  \
		$(OBJ_DIR)/TodolistModel.o  $(OBJ_DIR)/TodolistStorage.o  \
		$(OBJ_DIR)/cJSON.o  $(OBJ_DIR)/main.o
		
	$(CC) $(CC_FLAG) $^ -lm -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c  $(INC_DIR)/TodolistConsole.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/TodolistConsole.o: $(SRC_DIR)/TodolistConsole.c  $(INC_DIR)/TodolistConsole.h  \
		$(INC_DIR)/TodolistService.h  $(INC_DIR)/TodolistModel.h  $(INC_DIR)/TodolistErrorCode.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/TodolistService.o: $(SRC_DIR)/TodolistService.c  $(INC_DIR)/TodolistService.h  \
		$(INC_DIR)/TodolistModel.h  $(INC_DIR)/TodolistStorage.h  $(INC_DIR)/TodolistErrorCode.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/TodolistModel.o: $(SRC_DIR)/TodolistModel.c  $(INC_DIR)/TodolistModel.h  \
		$(INC_DIR)/TodolistStorage.h  $(INC_DIR)/TodolistErrorCode.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/TodolistStorage.o: $(SRC_DIR)/TodolistStorage.c  $(INC_DIR)/TodolistStorage.h  \
		$(INC_DIR)/TodolistModel.h  $(INC_DIR)/TodolistErrorCode.h  $(LIB_DIR)/cJSON.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/cJSON.o:
	cd $(LIB_DIR) && make CC=$(CC)

$(INC_DIR)/*.h:
	touch *.h

clean:
	rm -rf $(OBJ_DIR)/*.o main
