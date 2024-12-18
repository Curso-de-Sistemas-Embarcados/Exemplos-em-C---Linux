BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/

CC := gcc
CFLAGS := -Wall

SRCFILES := $(wildcard *.c)

all: $(SRCFILES:%.c=%.o)
	$(CC) $(CFLAGS) *.o -o bin_main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf bin_main

run:
	./bin_main