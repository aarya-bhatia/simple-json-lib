#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"

void json_free(json_t *json)
{
    if (!json)
    {
        return;
    }

    free(json->key);
    json->key = NULL;

    if (json->child)
    {
        _json_val_free(json->child, VAL_OBJ);
    }

    if (json->sibling)
    {
        _json_val_free(json->sibling, VAL_OBJ);
    }

    _json_val_free(json->value, json->vtype);
    json->value = NULL;

    free(json);
}

void _json_val_free(void *value, vtype_t type)
{
    if (type == VAL_STR)
    {
        free(value);
    }

    else if (type == VAL_OBJ)
    {
        json_free(value);
    }
}

json_t *json_copy(json_t *json)
{
    assert(json);

    json_t *new_json = calloc(1, sizeof *new_json);
    new_json->key = strdup(json->key);
    new_json->value = _json_val_copy(json->value, json->vtype);
    new_json->sibling = json->sibling ? json_copy(json->sibling) : NULL;
    new_json->child = json->child ? json_copy(json->child) : NULL;

    return new_json;
}

void *_json_val_copy(void *value, vtype_t type)
{
    assert(value);

    if (type == VAL_STR)
    {
        return strdup(value);
    }

    else if (type == VAL_OBJ)
    {
        return json_copy(value);
    }

    return value;
}

json_t *json_get(json_t *json, const char *key)
{
    assert(json);
    assert(key);

    for (json_t *itr = json->child; itr; itr = itr->sibling)
    {
        if (!strcmp(itr->key, key))
        {
            return itr;
        }
    }

    return NULL;
}

void json_set(json_t *json, const char *key, void *value, vtype_t vtype)
{
    assert(json);
    assert(key);

    // check if key exists
    json_t *found = NULL;
    if ((found = json_get(json, key)) != NULL)
    {
        // free old value
        _json_val_free(found->value, found->vtype);

        // copy new value
        found->vtype = vtype;
        found->value = _json_val_copy(value, vtype);
        return;
    }

    // create new json obj
    json_t *node = calloc(1, sizeof *node);
    assert(node);

    // copy key
    node->key = strdup(key);

    // copy value
    node->vtype = vtype;
    node->value = _json_val_copy(value, vtype);

    // add new obj to linked list
    node->sibling = json->child;
    json->child = node;
}