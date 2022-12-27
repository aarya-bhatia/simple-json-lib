#include "types.h"
#include "StringLibrary.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void *object_constructor(copy_constructor_type copy_constructor,
                         destructor_type destructor,
                         to_string_type to_string)
{
    object_t *object = malloc(sizeof *object);

    object->copy_constructor = copy_constructor ? copy_constructor : shallow_copy_constructor;
    object->destructor = destructor ? destructor : shallow_destructor;
    object->to_string = to_string ? to_string : shallow_to_string;
    object->elem = NULL;

    return object;
}

void *object_default_constructor()
{
    return object_constructor(NULL, NULL, NULL);
}

void *object_copy_constructor(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    object_t *object = (object_t *)elem;

    object_t *new_object = malloc(sizeof *new_object);
    new_object->copy_constructor = object->copy_constructor;
    new_object->destructor = object->destructor;
    new_object->elem = object->copy_constructor(object->elem);

    return new_object;
}

void object_destructor(void *elem)
{
    if (!elem)
    {
        return;
    }

    object_t *object = (object_t *)elem;
    object->destructor(object->elem);

    free(object);
}

char *object_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    object_t *object = (object_t *)elem;
    return object->to_string(object->elem);
}

void object_set(object_t *object, void *elem)
{
    assert(object);
    object->elem = object->copy_constructor(elem);
}

void *object_get(object_t *object)
{
    assert(object);
    return object->elem;
}

void *null_default_constructor()
{
    return NULL;
}

void *null_copy_constructor(void *elem)
{
    (void)elem;
    return NULL;
}

void null_destructor(void *elem)
{
    (void)elem;
}

char *null_to_string(void *elem)
{
    (void)elem;
    return strdup("null");
}

void *string_default_constructor()
{
    return calloc(1, 1);
}

void *string_copy_constructor(void *elem)
{
    return elem ? strdup(elem) : NULL;
}

void string_destructor(void *elem)
{
    free(elem);
}

char *string_to_string(void *elem)
{
    return elem ? strdup(elem) : NULL;
}

void *string_constructor(char *str)
{
    return string_copy_constructor(str);
}

void *number_default_constructor()
{
    return calloc(1, sizeof(double));
}

void *number_copy_constructor(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    double *num = malloc(sizeof *num);
    *num = *(double *)elem;
    return num;
}

void number_destructor(void *elem)
{
    free(elem);
}

char *number_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    double num = *(double *)elem;
    char *s;
    asprintf(&s, "%f", num);
    return s;
}

void *boolean_default_constructor()
{
    return calloc(1, 1);
}

void *boolean_copy_constructor(void *elem)
{
    if (!elem)
    {
        return NULL;
    }
    char *boolean = malloc(sizeof *boolean);
    *boolean = *(char *)elem;
    return boolean;
}

void boolean_destructor(void *elem)
{
    free(elem);
}

char *boolean_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    return *(char *)elem == 0 ? strdup("false") : strdup("true");
}

void *shallow_default_constructor() { return NULL; }
void shallow_destructor(void *elem) { (void)elem; }
void *shallow_copy_constructor(void *elem) { return elem; }
char *shallow_to_string(void *elem) { return NULL; }