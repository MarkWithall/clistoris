CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra 
#CFLAGS=-std=c11 -Wall -Wextra
BIN=bin
OBJ=obj

ifdef COMSPEC
	RM := cmd /C del
	OUTPUT := $(BIN)\polymorphic_lists.exe
	TESTS := $(BIN)\array_list_iterator_tests.exe
	MKDIR := md
else
	RM := rm -f
	OUTPUT := $(BIN)/polymorphic_lists
	TESTS := $(BIN)/array_list_iterator_tests
	MKDIR := mkdir -p
endif

.PHONY: clean create_build_dirs

all: create_build_dirs $(OUTPUT) $(TESTS)

create_build_dirs:
	$(MKDIR) $(BIN) $(OBJ)

$(OBJ)/test.o: test.c test.h
	$(CC) $(CFLAGS) -o $(OBJ)/test.o -c test.c

$(OBJ)/list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -o $(OBJ)/list_data.o -c list_data.c

$(OBJ)/array_list.o: array_list.c array_list.h interfaces.h $(OBJ)/list_data.o
	$(CC) $(CFLAGS) -o $(OBJ)/array_list.o -c array_list.c

$(OUTPUT): polymorphic_lists.c $(OBJ)/array_list.o
	$(CC) $(CFLAGS) -o $(OUTPUT) polymorphic_lists.c $(OBJ)/array_list.o $(OBJ)/list_data.o

$(TESTS): array_list_iterator_tests.c $(OBJ)/array_list.o $(OBJ)/test.o
	$(CC) $(CFLAGS) -o $(TESTS) array_list_iterator_tests.c $(OBJ)/array_list.o $(OBJ)/list_data.o $(OBJ)/test.o

clean:
	$(RM) $(OUTPUT) $(TESTS) $(OBJ)/*.o

