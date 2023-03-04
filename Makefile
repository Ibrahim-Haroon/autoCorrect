CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o stdmap.o stdstring.o

autoCorrect: $(OBJECTS)
	$(CC) $(CFLAGS) -o autoCorrect $(OBJECTS)
main.o: main.c stdmap.h stdstring.h
	$(CC) $(CFLAGS) -c main.c -o main.o
stdstring.o: stdstring.c stdstring.h
	$(CC) $(CFLAGS) -c stdstring.c -o stdstring.o
stdmap.o: stdmap.c stdmap.h stdstring.h
	$(CC) $(CFLAGS) -c stdmap.c -o stdmap.o
clean:
	rm autoCorrect $(OBJECTS)
