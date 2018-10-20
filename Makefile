CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncurses

.PHONY: all clean

all: client

clean:
	    $(RM) *~ *.o roulette

OBJECTS=roulette.o
client: $(OBJECTS)
	    $(CC) $(CFLAGS) $(OBJECTS) -o roulette $(LDFLAGS)
