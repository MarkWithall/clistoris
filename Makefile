CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra 
#CFLAGS=-std=c11 -Wall -Wextra
#RM=cmd /C del
RM=rm -f
#OUTPUT=polymorphic_lists.exe
OUTPUT=polymorphic_lists

.PHONY: clean

all: $(OUTPUT) array_list_iterator_tests

test.o: test.c test.h
	$(CC) $(CFLAGS) -c test.c

list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -c list_data.c

array_list.o: array_list.c array_list.h interfaces.h list_data.o
	$(CC) $(CFLAGS) -c array_list.c

$(OUTPUT): polymorphic_lists.c array_list.o
	$(CC) $(CFLAGS) -o $(OUTPUT) polymorphic_lists.c array_list.o list_data.o

array_list_iterator_tests: array_list_iterator_tests.c array_list.o test.o
	$(CC) $(CFLAGS) -o array_list_iterator_tests array_list_iterator_tests.c array_list.o list_data.o test.o

clean:
	$(RM) $(OUTPUT) *.o array_list_iterator_tests

