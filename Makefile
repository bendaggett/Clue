OBJECTS = items.o \
	rooms.o \
	characters.o \
	adventure.o

CFLAGS = -g -O2 -std=c99 -Wall -Wpedantic -D_POSIX_C_SOURCE=200809L

clue: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
