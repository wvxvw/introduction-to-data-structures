CC := gcc
SOURCES := $(wildcard ./*.c)
LIB := $(abspath ../lib)
OBJECTS := $(SOURCES:.c=.o)
CFLAGS := -Wall -fPIC -ggdb -I$(LIB)
SHARED :=  -L$(LIB) -lassignments -lgc -lm
PROGRAM := assignment-1.8

default: program

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

program: $(OBJECTS)
	$(CC) $(CFLAGS) $(SHARED) $(OBJECTS) -o $(PROGRAM)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(PROGRAM)

check-syntax:
	$(CC) -o nul -S $(SOURCES)
