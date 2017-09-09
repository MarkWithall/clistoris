include TESTickle/TESTickle.mk

CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra -Werror -g -Wno-microsoft
#CFLAGS=-std=c11 -Wall -Wextra -Werror
BIN=bin
OBJ=obj
PERL=perl

CFLAGS += -I TESTickle

ifeq ($(OS),Windows_NT)
	RM := cmd /C del
	MKDIR := cmd /C md
	OBJECTS := $(OBJ)\\*.o *.o
	BINARIES := $(BIN)\\*.exe
	DOTEXE := .exe
else
	RM := rm -f
	MKDIR := mkdir -p
	OBJECTS := $(OBJ)/*.o *.o
	BINARIES := $(BIN)/*
	DOTEXE := 
endif

.PHONY: test clean create_build_dirs
.IGNORE: create_build_dirs

all: create_build_dirs \
	$(BIN)/array_list_iterator.test$(DOTEXE) \
	$(BIN)/array_list_collection.test$(DOTEXE) \
	$(BIN)/array_list_list.test$(DOTEXE) \
	$(BIN)/linked_list_iterator.test$(DOTEXE) \
	$(BIN)/linked_list_collection.test$(DOTEXE) \
	$(BIN)/linked_list_list.test$(DOTEXE)

create_build_dirs:
	$(MKDIR) $(BIN) $(OBJ)

$(OBJ)/list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -o $@ -c list_data.c

$(OBJ)/array_list.o: array_list.c array_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c array_list.c

$(OBJ)/linked_list.o: linked_list.c linked_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c linked_list.c

$(BIN)/array_list_iterator.test$(DOTEXE): $(call test_files_for,array_list_iterator.test.c) $(OBJ)/array_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^ 

$(BIN)/array_list_collection.test$(DOTEXE): $(call test_files_for,array_list_collection.test.c) $(OBJ)/array_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/array_list_list.test$(DOTEXE): $(call test_files_for,array_list_list.test.c) $(OBJ)/array_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_iterator.test$(DOTEXE): $(call test_files_for,linked_list_iterator.test.c) $(OBJ)/linked_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_collection.test$(DOTEXE): $(call test_files_for,linked_list_collection.test.c) $(OBJ)/linked_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_list.test$(DOTEXE): $(call test_files_for,linked_list_list.test.c) $(OBJ)/linked_list.o $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ $^

test:
	prove -f -e "" $(BIN)/*$(DOTEXE)

clean:
	$(RM) $(BINARIES) $(OBJECTS) *_runner.c *.test.runner.c

