CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra -Werror
#CFLAGS=-std=c11 -Wall -Wextra -Werror
PERL=perl
BIN=bin
OBJ=obj

ifeq ($(OS),Windows_NT)
	RM := cmd /C del
	MKDIR := cmd /C md
	OBJECTS := $(OBJ)\*.o
	BINARIES := $(BIN)\*.*
	DOTEXE := .exe
else
	RM := rm -f
	MKDIR := mkdir -p
	OBJECTS := $(OBJ)/*.o
	BINARIES := $(BIN)/*
	DOTEXE := 
endif

.PHONY: clean create_build_dirs
.IGNORE: create_build_dirs

all: create_build_dirs $(BIN)/array_list_iterator_tests$(DOTEXE) $(BIN)/array_list_collection_tests$(DOTEXE) $(BIN)/array_list_list_tests$(DOTEXE)

create_build_dirs:
	$(MKDIR) $(BIN) $(OBJ)

$(OBJ)/test.o: test.c test.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/array_list.o: array_list.c array_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/array_list_iterator_tests.o: array_list_iterator_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/array_list_collection_tests.o: array_list_collection_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/array_list_list_tests.o: array_list_list_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c $<

array_list_iterator_tests_runner.c: array_list_iterator_tests.c
	$(PERL) test_generator.pl $< > $@

array_list_collection_tests_runner.c: array_list_collection_tests.c
	$(PERL) test_generator.pl $< > $@

array_list_list_tests_runner.c: array_list_list_tests.c
	$(PERL) test_generator.pl $< > $@

$(BIN)/array_list_iterator_tests$(DOTEXE): array_list_iterator_tests_runner.c $(OBJ)/array_list_iterator_tests.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)/array_list_iterator_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o

$(BIN)/array_list_collection_tests$(DOTEXE): array_list_collection_tests_runner.c $(OBJ)/array_list_collection_tests.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)/array_list_collection_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o

$(BIN)/array_list_list_tests$(DOTEXE): array_list_list_tests_runner.c $(OBJ)/array_list_list_tests.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)/array_list_list_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o

clean:
	$(RM) $(BINARIES) $(OBJECTS) *_runner.c

