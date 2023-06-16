CC = g++
CFLAGS = -g -Werror -I .

all: homework2

homework2: main.o
	$(CC) $(CFLAGS) -o homework2 main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp