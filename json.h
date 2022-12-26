#pragma once

#include "types.h"
#include "common.h"
#include "StringLibrary.h"
#include <sys/types.h>

json_object_t *json_object_emplace(json_object_t *json, const char *key, json_type type, void *value);

json_base_t *json_object_get(json_object_t *json, const char *key);
json_object_t *json_object_set(json_object_t *json, const char *key, json_base_t *value);

json_base_t *json_array_get(json_array_t *json, size_t index);
json_array_t *json_array_add(json_array_t *json, json_base_t *value);

char *json_string_get(json_string_t *json);
void json_string_set(json_string_t *json, const char *content);

double json_number_get(json_number_t *json);
void json_number_set(json_number_t *json, double new_number);

char json_boolean_get(json_boolean_t *json);
void json_boolean_set(json_boolean_t *json, char new_boolean);


#define json_object_iterator(arr, itr, callback) \
	{                                            \
		for (itr = arr; itr; itr = itr->next)    \
			callback;                            \
	}

#define json_array_iterator(arr, itr, callback) \
	{                                           \
		for (itr = arr; itr; itr = itr->next)   \
			callback;                           \
	}

json_base_t *json_base_create(json_type, void *);
json_base_t *json_base_clone(json_base_t *);
void json_base_free(json_base_t *);
String *json_base_to_string(json_base_t *);

json_object_t *json_object_create();
json_object_t *json_object_clone(json_object_t *);
void json_object_free(json_object_t *);
String *json_object_to_string(json_object_t *);

json_array_t *json_array_create();
json_array_t *json_array_clone(json_array_t *);
void json_array_free(json_array_t *);
String *json_array_to_string(json_array_t *);

json_string_t *json_string_create(const char *string);
json_string_t *json_string_clone(json_string_t *);
void json_string_free(json_string_t *);
String *json_string_to_string(json_string_t *);

json_number_t *json_number_create(double number);
json_number_t *json_number_clone(json_number_t *);
void json_number_free(json_number_t *);
String *json_number_to_string(json_number_t *);

json_boolean_t *json_boolean_create(char boolean);
json_boolean_t *json_boolean_clone(json_boolean_t *);
void json_boolean_free(json_boolean_t *);
String *json_boolean_to_string(json_boolean_t *);
