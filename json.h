#pragma once

#include "common.h"
#include "sstring.h"

enum _json_type
{
    json_type_null,
    json_type_array,
    json_type_object,
    json_type_string
};

struct _json_t
{
    void *value;
    enum _json_type type;
};

struct _json_object_t
{
    char *key;
    struct _json_t *value;
    struct _json_object_t *next;
};

struct _json_array_t
{
    struct _json_t *value;
    struct _json_array_t *next;
};

typedef enum _json_type json_type;
typedef struct _json_array_t json_array_t;
typedef struct _json_object_t json_object_t;
typedef struct _json_t json_t;

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


void json_free(json_t *json);
void json_array_free(json_array_t *);
void json_object_free(json_object_t *);

json_t *json_create();
json_array_t *json_array_create();
json_object_t *json_object_create();

json_t *json_clone(json_t *json);
json_array_t *json_array_clone(json_array_t *);
json_object_t *json_object_clone(json_object_t *);

void json_object_set(json_object_t *obj, const char *key, json_t *value, bool shallow_copy);
json_t *json_object_get(json_object_t *json, const char *key);

size_t json_array_size(json_array_t *arr);

/**
 * @brief Gets the json array entry at position index in the json array.
 * Returns null if none found.
 * 
 * @param arr 
 * @param index 
 * @return json_t* 
 */
json_array_t *json_array_get(json_array_t *arr, size_t index);
void json_array_add(json_array_t *json, json_array_t *entry);


char *json_to_string(json_t *json);
json_t *json_parse_string(char *str);
