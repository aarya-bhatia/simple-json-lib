#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "sstring.h"

void json_add_child(json_t *parent, json_t *child)
{
    child->sibling = parent->child;
    parent->child = child;
}

void json_free(json_t *json)
{
    if (!json)
    {
        return;
    }

    if (json->key)
    {
        free(json->key);
        json->key = NULL;
    }

    if (json->child)
    {
        json_free(json->child);
        json->child = NULL;
    }

    if (json->sibling)
    {
        json_free(json->sibling);
        json->sibling = NULL;
    }

    if (json->value)
    {
        _json_val_free(json->value, json->vtype);
        json->value = NULL;
    }

    free(json);
}

void _json_val_free(void *value, vtype_t type)
{
    if (!value)
    {
        return;
    }

    if (type == VAL_OBJ)
    {
        json_free(value);
    }
    else
    {
        free(value);
    }
}

json_t *json_copy(const json_t *json)
{
    assert(json);

    // the copy object
    json_t *new_json = calloc(1, sizeof *new_json);

    if (json->key)
    {
        new_json->key = strdup(json->key);
    }

    // copy the children
    for (json_t *itr = (json_t *)json->child; itr; itr = itr->sibling)
    {
        json_t *child = json_copy(itr);
        json_add_child(new_json, child);
    }

    // Do not copy siblings

    return new_json;
}

void *_json_val_copy(const void *value, vtype_t type)
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

    else
    {
        void *new_value = NULL;

        if (type == VAL_INT)
        {
            new_value = malloc(sizeof(int));
            memcpy(new_value, value, sizeof(int));
        }
        else if (type == VAL_FLOAT)
        {
            new_value = malloc(sizeof(float));
            memcpy(new_value, value, sizeof(float));
        }
        else if (type == VAL_CHAR)
        {
            new_value = malloc(sizeof(char));
            memcpy(new_value, value, sizeof(char));
        }
        else if (type == VAL_BOOL)
        {
            new_value = malloc(sizeof(bool));
            memcpy(new_value, value, sizeof(bool));
        }

        return new_value;
    }
}

json_t *json_get(const json_t *json, const char *key)
{
    assert(json);
    assert(key);

    for (json_t *itr = json->child; itr; itr = itr->sibling)
    {
        if (itr->key && !strcmp(itr->key, key))
        {
            return itr;
        }
    }

    return NULL;
}

void json_set(json_t *parent, const char *key, const void *value, vtype_t vtype)
{
    assert(parent);
    assert(key);

    // check if key exists
    json_t *found = NULL;

    if ((found = json_get(parent, key)) != NULL)
    {
        // free old value
        _json_val_free(found->value, found->vtype);

        // copy new value
        found->vtype = vtype;
        found->value = _json_val_copy(value, vtype);

        return;
    }

    // create new parent obj
    json_t *child = calloc(1, sizeof *child);
    assert(child);

    // copy key
    child->key = strdup(key);

    // copy value
    child->vtype = vtype;
    child->value = _json_val_copy(value, vtype);

    // add new obj to linked list
    json_add_child(parent, child);
}

void json_to_string(sstring *s, json_t *json)
{
    /*
    { 'key': 'value', ... }
    { 'key': { 'value.key': value, ... }}
    */
    assert(json);

    for (json_t *itr = json->child; itr; itr = itr->sibling)
    {
        if (itr->key)
        {
            sstring_putc(s, '\"');
            sstring *s_tmp = cstr_to_sstring(itr->key);
            sstring_append(s, s_tmp);
            sstring_destructor(s_tmp);
            sstring_putc(s, '\"');
            sstring_putc(s, ':');
            sstring_putc(s, ' ');
        }

        if (itr->vtype == VAL_STR)
        {
            sstring_putc(s, '\"');
            sstring *s_tmp = cstr_to_sstring(itr->value);
            sstring_append(s, s_tmp);
            sstring_destructor(s_tmp);
            sstring_putc(s, '\"');
        }

        else if (itr->vtype == VAL_INT)
        {
            char tmp[128];
            sprintf(tmp, "%d", *(int *)itr->value);
            sstring *s_tmp = cstr_to_sstring(tmp);
            sstring_append(s, s_tmp);
            sstring_destructor(s_tmp);
        }

        else if (itr->vtype == VAL_FLOAT)
        {
            char tmp[128];
            sprintf(tmp, "%f", *(float *)itr->value);
            sstring *s_tmp = cstr_to_sstring(tmp);
            sstring_append(s, s_tmp);
            sstring_destructor(s_tmp);
        }

        else if (itr->vtype == VAL_CHAR)
        {
            sstring_putc(s, '\'');
            sstring_putc(s, *(char *)itr->value);
            sstring_putc(s, '\'');
        }

        else if (itr->vtype == VAL_BOOL)
        {
            sstring *tmp = NULL;
            if (*(char *)itr->value == 0)
            {
                tmp = cstr_to_sstring("false");
                sstring_append(s, tmp);
            }
            else
            {
                tmp = cstr_to_sstring("true");
                sstring_append(s, tmp);
            }
            sstring_destructor(tmp);
        }

        else if (itr->vtype == VAL_OBJ)
        {
            sstring_putc(s, '{');

            sstring *inner_str = sstring_default_constructor();
            json_to_string(inner_str, itr->value);
            sstring_append(s, inner_str);
            sstring_destructor(inner_str);

            sstring_putc(s, '}');
        }

        sstring_putc(s, ',');
    }
}
