CC=gcc
LD=gcc

OBJ_DIR=.objs
SRC_DIR=src

INCLUDES=-I. -Iincludes -Isrc
WARNINGS=-Wall -Wextra -Werror
CFLAGS= $(WARNINGS) $(INCLUDES) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -O0 -DDEBUG
CPPFLAGS= $(WARNINGS) $(INCLUDES) -g -std=c++11 -c -MMD -MP -O0

FILES=$(shell find src Aarya -type f -name "*.c")
OBJ=$(FILES:%.c=$(OBJ_DIR)/%.o)

all: main json_test ht_test tags

main: $(OBJ_DIR)/Aarya/json.o
	g++ $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@);
	g++ -std=c++11 -Wall -g -c $< -o $@

json_test: $(OBJ) $(OBJ_DIR)/test/json_test.o
	$(LD) $^ -o $@ 

ht_test: $(OBJ) $(OBJ_DIR)/test/ht_test.o
	$(LD) $^ -o $@ 

string_test: $(OBJ_DIR)/test/string_test.o $(OBJ)
	$(LD) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) -o $@ $<

tags:
	ctags -R *

clean:
	rm -rf $(OBJ_DIR) json ht_test json_test string_test

-include $(OBJ_DIR)/*.d
