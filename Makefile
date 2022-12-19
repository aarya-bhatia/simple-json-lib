OBJS=json.o sstring.o vector.o callbacks.o

all: main # test

main: $(OBJS) main.o 
	gcc -std=gnu99 -I. $^ -o $@

%.o: %.c
	gcc -Wall -Wextra -Werror -Wno-unused-parameter -g -pedantic -std=gnu99 -c $< -o $@

clean:
	rm -rf $(OBJS)