#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "util.h"


json_object_t *json_object_constructor(copy_constructor_type value_copy_constructor,
                                       destructor_type value_destructor,
                                       to_string_type value_to_string)
{
    json_object_t *json = calloc(1, sizeof *json);
    json->value = object_constructor(value_copy_constructor, value_destructor, value_to_string);
    return json;
}

json_object_t *json_object_copy_constructor(json_object_t *json)
{
    if (!json)
    {
        return NULL;
    }

    json_object_t *new_json = json_object_constructor(json->value->copy_constructor, json->value->destructor, json->value->to_string);

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

char *_json_object_to_string(json_object_t *json)
{
    String *s = StringDefaultConstructor();

    String *tmp = wrap_with_quotes(json->key);
    StringAppend(s, tmp);
    StringDestructor(tmp);
    StringAddCstr(s, ": ");

    char *val_str = object_to_string(json->value);
    tmp = wrap_with_quotes(val_str);
    StringAppend(s, tmp);
    StringDestructor(tmp);
    free(val_str);

    if (json->next)
    {
        StringAdd(s, ',');
        StringAdd(s, ' ');
        char *next = _json_object_to_string(json->next);
        StringAddCstr(s, next);
        free(next);
    }

    char *c = StringToCstr(s);
    StringDestructor(s);
    return c;
}

char *json_object_to_string(json_object_t *json)
{
    if (!json)
    {
        return NULL;
    }

    String *s = StringDefaultConstructor();

    StringAdd(s, '{');

    char *content = _json_object_to_string(json);
    StringAddCstr(s, content);
    free(content);

    StringAdd(s, '}');

    char *c = StringToCstr(s);
    StringDestructor(s);
    return c;
}
