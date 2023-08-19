CC:=gcc
Cflags:= -g -Wall

all:s_tree.c
	$(CC) main.c -o main.out

bench:

clean:
	rm -f main.out