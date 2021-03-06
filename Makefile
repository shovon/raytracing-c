CC := gcc
OBJ := obj
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
OUTNAME := $(notdir $(CURDIR))

all: $(OBJECTS)
	$(CC) -O3 $^ -o $(OUTNAME)

%.o: %.c
	$(CC) -O3 -I. -c $< -o $@

clean:
	rm *.o $(OUTNAME)