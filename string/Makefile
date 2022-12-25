all: main

string: string.o
	ar rcs libstring.a string.o

main: string main.o
	gcc -std=c99 -o $@ main.o libstring.a

%.o: %.c
	gcc -Wall -std=c99 -g -c -o $@ $<

tags:
	ctags .

clean:
	rm *.o *.a main tags
