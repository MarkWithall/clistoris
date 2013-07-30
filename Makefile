CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra -Werror -g
#CFLAGS=-std=c11 -Wall -Wextra -Werror
BIN=bin
OBJ=obj
PERL=perl

ifeq ($(OS),Windows_NT)
	RM := cmd /C del
	MKDIR := cmd /C md
	OBJECTS := $(OBJ)\*.o
	BINARIES := $(BIN)\*.exe
	DOTEXE := .exe
else
	RM := rm -f
	MKDIR := mkdir -p
	OBJECTS := $(OBJ)/*.o
	BINARIES := $(BIN)/*
	DOTEXE := 
endif

.PHONY: test clean create_build_dirs
.IGNORE: create_build_dirs

all: create_build_dirs \
	$(BIN)/array_list_iterator_tests$(DOTEXE) \
	$(BIN)/array_list_collection_tests$(DOTEXE) \
	$(BIN)/array_list_list_tests$(DOTEXE) \
	$(BIN)/linked_list_iterator_tests$(DOTEXE) \
	$(BIN)/linked_list_collection_tests$(DOTEXE) \
	$(BIN)/linked_list_list_tests$(DOTEXE)

create_build_dirs:
	$(MKDIR) $(BIN) $(OBJ)

$(OBJ)/test.o: test.c test.h
	$(CC) $(CFLAGS) -o $@ -c test.c

$(OBJ)/list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -o $@ -c list_data.c

$(OBJ)/array_list.o: array_list.c array_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c array_list.c

$(OBJ)/linked_list.o: linked_list.c linked_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $@ -c linked_list.c

$(OBJ)/array_list_iterator_tests.o: array_list_iterator_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c array_list_iterator_tests.c

$(OBJ)/array_list_collection_tests.o: array_list_collection_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c array_list_collection_tests.c

$(OBJ)/array_list_list_tests.o: array_list_list_tests.c $(OBJ)/test.o $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $@ -c array_list_list_tests.c

$(OBJ)/linked_list_iterator_tests.o: linked_list_iterator_tests.c $(OBJ)/test.o $(OBJ)/linked_list.o
	$(CC) $(CFLAGS) -o $@ -c linked_list_iterator_tests.c

$(OBJ)/linked_list_collection_tests.o: linked_list_collection_tests.c $(OBJ)/test.o $(OBJ)/linked_list.o
	$(CC) $(CFLAGS) -o $@ -c linked_list_collection_tests.c

$(OBJ)/linked_list_list_tests.o: linked_list_list_tests.c $(OBJ)/test.o $(OBJ)/linked_list.o
	$(CC) $(CFLAGS) -o $@ -c linked_list_list_tests.c

array_list_iterator_tests_runner.c: array_list_iterator_tests.c
	$(PERL) test_generator.pl $< > $@

array_list_collection_tests_runner.c: array_list_collection_tests.c
	$(PERL) test_generator.pl $< > $@

array_list_list_tests_runner.c: array_list_list_tests.c
	$(PERL) test_generator.pl $< > $@

linked_list_iterator_tests_runner.c: linked_list_iterator_tests.c
	$(PERL) test_generator.pl $< > $@

linked_list_collection_tests_runner.c: linked_list_collection_tests.c
	$(PERL) test_generator.pl $< > $@

linked_list_list_tests_runner.c: linked_list_list_tests.c
	$(PERL) test_generator.pl $< > $@

$(BIN)/array_list_iterator_tests$(DOTEXE): array_list_iterator_tests_runner.c $(OBJ)/array_list_iterator_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^ 

$(BIN)/array_list_collection_tests$(DOTEXE): array_list_collection_tests_runner.c $(OBJ)/array_list_collection_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/array_list_list_tests$(DOTEXE): array_list_list_tests_runner.c $(OBJ)/array_list_list_tests.o $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_iterator_tests$(DOTEXE): linked_list_iterator_tests_runner.c $(OBJ)/linked_list_iterator_tests.o $(OBJ)/linked_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_collection_tests$(DOTEXE): linked_list_collection_tests_runner.c $(OBJ)/linked_list_collection_tests.o $(OBJ)/linked_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/linked_list_list_tests$(DOTEXE): linked_list_list_tests_runner.c $(OBJ)/linked_list_list_tests.o $(OBJ)/linked_list.o $(OBJ)/list_data.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $@ $^

test:
	$(BIN)/array_list_iterator_tests
	$(BIN)/array_list_collection_tests
	$(BIN)/array_list_list_tests
	$(BIN)/linked_list_iterator_tests
	$(BIN)/linked_list_collection_tests
	$(BIN)/linked_list_list_tests

clean:
	$(RM) $(BINARIES) $(OBJECTS) *_runner.c

