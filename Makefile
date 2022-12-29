CC=gcc
LD=gcc

OBJ_DIR=.objs
SRC_DIR=src

INCLUDES=-I. -Iincludes -Isrc
WARNINGS=-Wall -Wextra -Werror -Wno-error=unused-parameter -Wmissing-declarations
CFLAGS= $(WARNINGS) $(INCLUDES) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -O0 -DDEBUG

FILES=$(shell find src lib Aarya -type f -name "*.c")
OBJ=$(FILES:%.c=$(OBJ_DIR)/%.o)

all: json_test ht_test

json_test: $(OBJ) $(OBJ_DIR)/test/test.o
	$(LD) $^ -o $@ 

ht_test: $(OBJ) $(OBJ_DIR)/test/ht_test.o
	$(LD) $^ -o $@ 

string_test: $(OBJ_DIR)/test/string_test.o $(OBJ)
	$(LD) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@);
	$(CC) $(CFLAGS) -o $@ $<

tags:
	ctags -R *

clean:
	rm -rf $(OBJ_DIR) main string_test tags

-include $(OBJ_DIR)/*.d
