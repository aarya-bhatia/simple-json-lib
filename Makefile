OBJS=json.o sstring.o vector.o callbacks.o

all: main example-1

main: main.o $(OBJS)
	gcc -std=gnu99 -I. $^ -o $@

example-%: example-%.o $(OBJS)
	gcc -std=gnu99 -I. $^ -o $@

%.o: %.c
	gcc -Wall -Wextra -Werror -Wno-unused-parameter -g -pedantic -std=gnu99 -c $< -o $@

clean:
	rm -rf *.o
