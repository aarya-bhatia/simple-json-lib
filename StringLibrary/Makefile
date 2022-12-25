all: main

main: String main.o
	gcc -std=c99 -o $@ main.o libstring.a

String: StringLibrary.o
	ar rcs libstring.a $^

%.o: %.c
	gcc -Wall -std=c99 -g -c -o $@ $<

tags:
	ctags .

clean:
	rm -rf *.o *.a main tags
