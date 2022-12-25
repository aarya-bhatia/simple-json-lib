CFLAGS= -Wall -g -pedantic -std=gnu99 -Istring -c
LDFLAGS= string/libstring.a

main: objs/main.o objs/json.o | string
	gcc $(LDFLAGS) -o $@ $^

objs/%.o: %.c
	mkdir -p objs;
	gcc $(CFLAGS) -o $@ $<

string:
	cd string && make string;

tags:
	ctags -R *

clean:
	rm -rf objs/ main tags;
	cd string && make clean;
