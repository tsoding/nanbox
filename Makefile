CFLAGS=-Wall -Wextra -std=c11 -pedantic
LIBS=

nanbox: main.c nanbox.h
	$(CC) $(CFLAGS) -o nanbox main.c $(LIBS)
