#pragma once

#include "sstring.h"

/**
 * @brief Represents the possible types for the value of a JSON object key.
 *
 */
typedef enum vtype_t
{
    VAL_NONE,
    VAL_STR,
    VAL_FLOAT,
    VAL_INT,
    VAL_CHAR,
    VAL_BOOL,
    VAL_OBJ,
} vtype_t;


/**
 * @brief Represents a JSON Object
 */
typedef struct _json_t
{
    // all keys are strings (owned by the object)
    char *key;

    // value can take many forms
    void *value;

    // vtype specifies the type of value
    vtype_t vtype;

    // Head of the list
    struct _json_t *child;

    // Next in the list
    struct _json_t *sibling;
} json_t;

/*********** Private Methods ************/
void _json_val_free(void *value, vtype_t type);
void *_json_val_copy(const void *value, vtype_t type);

/*********** Public Methods ************/

/**
 * @brief Returns a JSON object containing the given key from the base JSON object.
 *
 * @param json
 * @param key
 * @return json_t*
 */
json_t *json_get(const json_t *json, const char *key);

/**
 * @brief Update or insert a key and value of type vtype into the given JSON object.
 *
 * @param json
 * @param key
 * @param value
 * @param vtype
 */
void json_set(json_t *json, const char *key, const void *value, vtype_t vtype);

/**
 * @brief Deep copy a JSON Object
 *
 * @param json
 * @return json_t*
 */
json_t *json_copy(const json_t *json);

/**
 * @brief Free the memory allocated by a JSON Object and all its children.
 *
 * @param json
 */
void json_free(json_t *json);


/**
 * @brief Fill s with string representation of JSON object
 * 
 * @param s string buffer to store intermediate results
 * @param json 
 */
void json_to_string(sstring *s, json_t *json);
