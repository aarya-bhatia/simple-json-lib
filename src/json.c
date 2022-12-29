#include "json.h"

void *json_default_constructor(void)
{
    return calloc(1, sizeof(json_t));
}

char *json_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    json_t *json = (json_t *)elem;
    return object_to_string(json->object);
}

void *json_copy_constructor(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    json_t *json = (json_t *)elem;

    json_t *new_json = malloc(sizeof(json_t));
    new_json->type = json->type;
    new_json->object = object_copy_constructor(json->object);

    return NULL;
}

void json_destructor(void *elem)
{
    if (!elem)
    {
        return;
    }

    json_t *json = (json_t *)elem;

    object_destructor(json->object);
    free(json);
}

json_t *json_object_create()
{
    json_t *json = json_default_constructor();
    json->type = json_type_object;

    object_t *object = object_default_constructor();

    ht_t *ht = malloc(sizeof *ht);

    ht_init(ht, string_hash_function, string_compare, string_copy_constructor, string_destructor,
            string_to_string, json_copy_constructor, json_destructor, json_to_string);

    object->copy_constructor = ht_copy_constructor;
    object->destructor = ht_destructor;
    object->to_string = ht_to_string;
    object->elem = ht;

    json->object = object;

    return json;
}

json_t *json_string_create()
{
    json_t *json = json_default_constructor();
    json->type = json_type_string;
    json->object = object_constructor(NULL, string_default_constructor, string_copy_constructor, string_destructor, string_to_string);
    return json;
}

json_t *json_int_create()
{
    json_t *json = json_default_constructor();
    json->type = json_type_int;
    json->object = object_constructor(NULL, int_default_constructor, int_copy_constructor, int_destructor, int_to_string);
    return json;
}

json_t *json_double_create()
{
    json_t *json = json_default_constructor();
    json->type = json_type_double;
    json->object = object_constructor(NULL, double_default_constructor, double_copy_constructor, double_destructor, double_to_string);
    return json;
}

// vector *json_array_create()
// {
//     return vector_create(json_copy_constructor, json_destructor, json_default_constructor);
// }

// char *json_array_to_string()