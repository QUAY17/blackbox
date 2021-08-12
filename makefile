C = gcc
CFLAGS = -g -Wall -no-pie

all: main.o blackbox.o
	$(CC) $(CFLAGS) -o main main.o blackbox.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm *.o