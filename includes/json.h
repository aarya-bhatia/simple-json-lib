#pragma once

#include "common.h"
#include "object.h"
#include "vector.h"
#include "Aarya/ht.h"

typedef enum json_type
{
    json_type_null,
    json_type_array,
    json_type_object,
    json_type_string,
    json_type_boolean,
    json_type_int,
	json_type_float,
	json_type_double
} json_type;

typedef struct json_t
{
    json_type type;
    object_t *object;
} json_t;

void *json_default_constructor(void);
char *json_to_string(void *elem);
void *json_copy_constructor(void *elem);
void json_destructor(void *elem);

json_t *json_object_create();
json_t *json_string_create();
json_t *json_int_create();
json_t *json_double_create();