#pragma once

#include "types.h"
#include "common.h"
#include "String.h"
#include <sys/types.h>

#define json_object_iterator(arr, itr, callback) \
{\
    for(itr = arr; itr; itr = itr->next) \
        callback;                        \
}

#define json_array_iterator(arr, itr, callback) \
	{                                           \
		for (itr = arr; itr; itr = itr->next)   \
			callback;                           \
	}

json_object_t *json_object_create();
json_object_t *json_object_clone(json_object_t *);
void *json_object_free();

json_array_t *json_array_create();
json_array_t *json_array_clone(json_array_t *);
void *json_array_free();

json_string_t *json_string_create();
json_string_t *json_string_clone(json_string_t *);
void *json_string_free();

json_number_t *json_number_create();
json_number_t *json_number_clone(json_number_t *);
void *json_number_free();

json_boolean_t *json_boolean_create();
json_boolean_t *json_boolean_clone(json_boolean_t *);
void *json_boolean_free();

String *json_to_string(json_base_t *json);
