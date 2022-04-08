OBJ := obj
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
OUTNAME := $(notdir $(CURDIR))

all: $(OBJECTS)
	$(CC) $^ -o $(OUTNAME)

%.o: %.c
	$(CC) -I. -c $< -o $@

clean:
	rm *.o $(OUTNAME)