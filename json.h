#pragma once

#include "types.h"
#include "common.h"
#include "StringLibrary.h"
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


json_base_t *json_base_create();
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

json_string_t *json_string_create();
json_string_t *json_string_clone(json_string_t *);
void json_string_free(json_string_t *);
String *json_string_to_string(json_string_t *);

json_number_t *json_number_create();
json_number_t *json_number_clone(json_number_t *);
void json_number_free(json_number_t *);
String *json_number_to_string(json_number_t *);

json_boolean_t *json_boolean_create();
json_boolean_t *json_boolean_clone(json_boolean_t *);
void json_boolean_free(json_boolean_t *);
String *json_boolean_to_string(json_boolean_t *);
