#pragma once

#include "types.h"
#include "common.h"
#include "StringLibrary.h"
#include <sys/types.h>

typedef enum json_type
{
    json_type_null,
    json_type_array,
    json_type_object,
    json_type_string,
    json_type_boolean,
    json_type_number
} json_type;

typedef struct json_object_t
{
    char *key;
    object_t *value;
    struct json_object_t *next;
} json_object_t;

#define json_object_iterator(arr, itr, callback) \
    {                                            \
        for (itr = arr; itr; itr = itr->next)    \
            callback                             \
    }

#define json_string_object() json_object_constructor(string_copy_constructor, string_destructor, string_to_string)

#define json_number_object() json_object_constructor(number_copy_constructor, number_destructor, number_to_string)

#define json_boolean_object() json_object_constructor(boolean_copy_constructor, boolean_destructor, boolean_to_string)

json_object_t *json_object_constructor(copy_constructor_type value_copy_constructor,
                                       destructor_type value_destructor,
                                       to_string_type to_string);

json_object_t *json_object_copy_constructor(json_object_t *json);
void json_object_destructor(json_object_t *json);
char *json_object_to_string(json_object_t *json);

#define json_object_set_key(json, new_key) json->key = string_copy_constructor(new_key)
#define json_object_get_key(json) json->key
#define json_object_set_value(json, new_value) object_set(json->value, new_value)
#define json_object_get_value(json) object_get(json->value)