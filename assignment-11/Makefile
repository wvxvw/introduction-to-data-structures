CC := gcc
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:.c=.o)
CFLAGS := -Wall -fPIC
DOXYGEN := doxygen

default: program

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

program: $(OBJECTS)
	$(CC) $(OBJECTS) -o assignment_11

library: $(OBJECTS)
	$(CC) -shared -Wl,-soname,libdsassignments.so -o libdsassignments.so $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f assignment_11

check-syntax:
	$(CC) -o nul -S ${SOURCES}

doc:
	$(DOXYGEN)
