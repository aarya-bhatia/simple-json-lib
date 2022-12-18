#pragma once

#include "sstring.h"

typedef enum json_type
{
    json_type_null,
    json_type_array,
    json_type_object,
    json_type_string
} json_type;

struct _json_array_t;
struct _json_object_t;

typedef struct json_t
{
    void *value;
    json_type type;
} json_t;

typedef struct _json_obect_t
{
    char *key;
    json_t *value;
    struct _json_object_t *next;
} json_object_t;

typedef struct _json_array_t
{
    json_t *value;
    struct _json_array_t *next;
} json_array_t;

void json_free(json_t *json);
void json_string_free(json_t *json);
void json_array_free(json_t *json);
void json_object_free(json_t *json);

json_t *json_create();
json_t *json_empty();
json_t *json_string_create(char *content);
json_t *json_array_create();
json_t *json_object_create();

json_t *json_clone(json_t *json);
json_t *json_string_clone(json_t *json);
json_t *json_array_clone(json_t *json);
json_t *json_object_clone(json_t *json);


void json_object_set(json_t *json, char *key, json_t *value);
json_t *json_object_get(json_t *json, char *key);

void json_array_get(json_t *json, size_t index);
void json_array_add(json_t *json, json_t *entry);
void json_array_remove(json_t *json, size_t index);
