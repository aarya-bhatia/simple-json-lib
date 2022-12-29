#pragma once

#include "common.h"
#include "callbacks.h"
#include "string_callbacks.h"
#include "compare.h"

#define HT_DENSITY 0.6
#define HT_INITIAL_CAPACITY 11

typedef struct ht_node_t
{
	void *key;
	void *value;
	struct ht_node_t *next;
} ht_node_t;

typedef struct ht_t
{
	ht_node_t **table;
	size_t size;
	size_t capacity;

	hash_function_type hash_function;
	compare key_comparator;

	copy_constructor_type key_copy_constructor;
	destructor_type key_destructor;
	to_string_type key_to_string;

	copy_constructor_type value_copy_constructor;
	destructor_type value_destructor;
	to_string_type value_to_string;

} ht_t;

void ht_init(ht_t *ht,
			 hash_function_type hash_function,
			 compare key_comparator,
			 copy_constructor_type key_copy_constructor,
			 destructor_type key_destructor,
			 to_string_type key_to_string,
			 copy_constructor_type value_copy_constructor,
			 destructor_type value_destructor,
			 to_string_type value_to_string);

void ht_set(ht_t *ht, void *key, void *value);
void *ht_get(ht_t *ht, void *key);
void ht_destroy(ht_t *ht);

void *ht_copy_constructor(void *elem);
void ht_destructor(void *elem);
char *ht_to_string(void *elem);
