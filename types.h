#pragma once

typedef enum _json_type
{
    json_type_null,
    json_type_array,
    json_type_object,
    json_type_string,
    json_type_boolean,
    json_type_number
} json_type;

typedef struct _json_base_t
{
    void *value;
    json_type type;
} json_base_t;

typedef struct _json_object_t
{
    char *key;
    json_base_t *value;
    struct _json_object_t *next;
} json_object_t;

typedef struct _json_array_t
{
    json_base_t *value;
    struct _json_array_t *next;
} json_array_t;

typedef struct _json_string_t
{
    char *string;
} json_string_t;

typedef struct _json_number_t
{
    double number;
} json_number_t;

typedef struct _json_boolean_t
{
    char boolean;
} json_boolean_t;