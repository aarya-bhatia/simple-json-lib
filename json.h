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


object_t *json_string()
{
    return object_constructor(string_copy_constructor, string_destructor);
}

object_t *json_number()
{
    return object_constructor(number_copy_constructor, number_destructor);
}

object_t *json_booolean()
{
    return object_constructor(boolean_copy_constructor, boolean_destructor);
}

json_object_t *json_object_constructor(copy_constructor_type value_copy_constructor,
                                       destructor_type value_destructor)
{
    json_object_t *json = calloc(1, sizeof *json);
    json->value = object_constructor(value_copy_constructor, value_destructor);
    return json;
}

json_object_t *json_object_copy_constructor(json_object_t *json)
{
    if (!json)
    {
        return NULL;
    }

    json_object_t *new_json = json_object_constructor(json->value->copy_constructor, json->value->destructor);

    new_json->key = string_copy_constructor(json->key);
    new_json->next = json_object_copy_constructor(json->next);

    return new_json;
}

void json_object_destructor(json_object_t *json)
{
    if (!json)
    {
        return;
    }

    json->value->destructor(json->value);
    free(json->key);
    json_object_destructor(json->next);
    free(json);
}

