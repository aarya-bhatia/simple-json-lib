all: main

String: String.o
	ar rcs libstring.a String.o

main: String main.o
	gcc -std=c99 -o $@ main.o libstring.a

%.o: %.c
	gcc -Wall -std=c99 -g -c -o $@ $<

tags:
	ctags .

clean:
	rm -rf *.o *.a main tags
