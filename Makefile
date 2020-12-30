CFLAGS=-Wall -Wextra -std=c11 -pedantic
LIBS=

nanbox: ./src/main.c src/nanbox.h
	$(CC) $(CFLAGS) -o nanbox ./src/main.c $(LIBS)
