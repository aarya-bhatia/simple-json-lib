#include "types.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void *object_constructor(copy_constructor_type copy_constructor,
                         destructor_type destructor)
{
    object_t *object = malloc(sizeof *object);

    object->copy_constructor = copy_constructor ? copy_constructor : shallow_copy_constructor;
    object->destructor = destructor ? destructor : shallow_destructor;
    object->elem = NULL;

    return object;
}

void *object_default_constructor()
{
    return object_constructor(NULL, NULL);
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
    new_object->elem = object->elem ? object->copy_constructor(object->elem) : NULL;

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
    assert(!elem);
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
