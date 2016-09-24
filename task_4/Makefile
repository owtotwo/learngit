ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR)

# FrontEnd
$(OBJ_DIR)/frontend.o: $(OBJ_DIR)/TodolistConsole.o
	cp $< $@

$(OBJ_DIR)/TodolistConsole.o: $(SRC_DIR)/TodolistConsole.c  $(INC_DIR)/TodolistConsole.h  \
		$(INC_DIR)/TodolistService.h  $(INC_DIR)/TodolistModel.h  $(INC_DIR)/TodolistErrorCode.h
	$(CC) $(CC_FLAG) -c $< -o $@

# BackEnd
$(OBJ_DIR)/backend.o: $(OBJ_DIR)/TodolistService.o
	cp $< $@

$(OBJ_DIR)/TodolistService.o: $(SRC_DIR)/TodolistService.c  $(INC_DIR)/TodolistService.h  \
		$(INC_DIR)/TodolistModel.h  $(INC_DIR)/TodolistStorage.h  $(INC_DIR)/TodolistErrorCode.h
	$(CC) $(CC_FLAG) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)/*.o