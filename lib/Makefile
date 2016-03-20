CC := gcc
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:.c=.o)
CFLAGS := -Wall -fPIC -ggdb

default: library

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

library: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -Wl,-soname,libdsassignments.so -o libdsassignments.so $(OBJECTS)

clean:
	-rm -f $(OBJECTS)

check-syntax:
	$(CC) -o nul -S $(SOURCES)
