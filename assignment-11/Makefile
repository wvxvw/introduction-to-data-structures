CC := gcc
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:.c=.o)
CFLAGS := -Wall

default: program

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

program: $(OBJECTS)
	$(CC) $(OBJECTS) -o assignment_11

clean:
	-rm -f $(OBJECTS)
	-rm -f assignment_11

check-syntax:
	$(CC) -o nul -S ${SOURCES}
