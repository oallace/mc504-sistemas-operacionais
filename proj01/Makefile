.PHONY: all clean

all: filter.o pgm.o filter

filter: pgm.o filter.o
	gcc pgm.o filter.o -o filter

pgm.o: pgm.c
	gcc -c pgm.c

filter.o: filter.c
	gcc -c filter.c

clean:
	rm -f filter filter.o pgm.o
