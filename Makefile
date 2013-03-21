CC=gcc
CFLAGS=-fms-extensions -std=c99 -Wall -Wextra -g
#CFLAGS=-std=c11 -Wall -Wextra
#RM=cmd /C del
RM=rm -f
#OUTPUT=polymorphic_lists.exe
OUTPUT=polymorphic_lists

all: $(OUTPUT)

list_data.o: list_data.c list_data.h
	$(CC) $(CFLAGS) -c list_data.c

array_list.o: array_list.c array_list.h interfaces.h list_data.o
	$(CC) $(CFLAGS) -c array_list.c

$(OUTPUT): polymorphic_lists.c array_list.o
	$(CC) $(CFLAGS) -o $(OUTPUT) polymorphic_lists.c array_list.o list_data.o

clean:
	$(RM) $(OUTPUT) array_list.o list_data.o
