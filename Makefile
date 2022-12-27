INCLUDES=-IStringLibrary -I.
CFLAGS= -Wall -g -std=gnu99 $(INCLUDES) -c
LDFLAGS= StringLibrary/libstring.a

all: main tags

FILE=main.c json.c types.c util.c
OBJ=$(FILE:%.c=objs/%.o)

main: $(OBJ) | String
	gcc $(LDFLAGS) -o $@ $^

String:
	cd StringLibrary && make String;

objs/%.o: %.c
	mkdir -p objs;
	gcc $(CFLAGS) -o $@ $<

tags:
	ctags -R *

clean:
	rm -rf objs/ main tags;
	cd StringLibrary && make clean;
