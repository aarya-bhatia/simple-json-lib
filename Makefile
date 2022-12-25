CFLAGS= -Wall -g -std=gnu99 -IStringLibrary -c
LDFLAGS= StringLibrary/libstring.a

all: String main tags

main: objs/main.o objs/json.o | String
	gcc $(LDFLAGS) -o $@ $^

objs/%.o: %.c
	mkdir -p objs;
	gcc $(CFLAGS) -o $@ $<

String:
	cd StringLibrary && make String;

tags:
	ctags -R *

clean:
	rm -rf objs/ main tags;
	cd StringLibrary && make clean;
