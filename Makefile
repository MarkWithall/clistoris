CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra 
#CFLAGS=-std=c11 -Wall -Wextra
PERL=perl
BIN=bin
OBJ=obj

ifeq ($(OS),Windows_NT)
	RM := cmd /C del
	OUTPUT := $(BIN)\polymorphic_lists.exe
	TESTS := $(BIN)\array_list_iterator_tests.exe
	MKDIR := cmd /C md
	OBJECTS := $(OBJ)\*.o
	BINARIES := $(BIN)\*.*
else
	RM := rm -f
	OUTPUT := $(BIN)/polymorphic_lists
	TESTS := $(BIN)/array_list_iterator_tests
	MKDIR := mkdir -p
	OBJECTS := $(OBJ)/*.o
	BINARIES := $(BIN)/*
endif

.PHONY: clean create_build_dirs
.IGNORE: create_build_dirs

all: create_build_dirs $(OUTPUT) $(TESTS)

create_build_dirs:
	$(MKDIR) $(BIN) $(OBJ)

$(OBJ)/test.o: test.c test.h
	$(CC) $(CFLAGS) -o $@ -c test.c

$(OBJ)/list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -o $@ -c list_data.c

$(OBJ)/array_list.o: array_list.c array_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c array_list.c

$(OBJ)/array_list_iterator_tests.o: array_list_iterator_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c array_list_iterator_tests.c

$(OUTPUT): polymorphic_lists.c $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ polymorphic_lists.c $(OBJ)/array_list.o $(OBJ)/list_data.o

$(TESTS): $(OBJ)/array_list_iterator_tests.o
	$(PERL) test_generator.pl array_list_iterator_tests.c >array_list_iterator_tests_runner.c
	$(CC) $(CFLAGS) -o $@ array_list_iterator_tests_runner.c $(OBJ)/array_list_iterator_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(RM) array_list_iterator_tests_runner.c

clean:
	$(RM) $(BINARIES) $(OBJECTS)

