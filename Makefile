CC := gcc
OBJ := obj
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
OUTNAME := $(notdir $(CURDIR))

all: $(OBJECTS)
	$(CC) -std=gnu99 -D_DEFAULT_SOURCE -O3 -flto -DNDEBUG $^ -o $(OUTNAME)

%.o: %.c
	$(CC) -std=gnu99 -D_DEFAULT_SOURCE -O3 -flto -DNDEBUG -I. -c $< -o $@

clean:
	rm *.o $(OUTNAME)