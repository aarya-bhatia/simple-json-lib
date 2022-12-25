CFLAGS= -Wall -g -pedantic -std=gnu99 -I String -c
LDFLAGS= String/libstring.a

main: objs/main.o objs/json.o | String
	gcc $(LDFLAGS) -o $@ $^

objs/%.o: %.c
	mkdir -p objs;
	gcc $(CFLAGS) -o $@ $<

String:
	cd String && make String;

tags:
	ctags -R *

clean:
	rm -rf objs/ main tags;
	cd String && make clean;
