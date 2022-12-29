#include "Aarya/String.h"
#include "common.h"
#include "object.h"

char *empty_string(void *elem);

char *empty_string(void *elem){
	(void)elem;
	return calloc(1,1);
}

void *object_constructor(void *elem,
		default_constructor_type default_constructor,
		copy_constructor_type copy_constructor,
		destructor_type destructor,
		to_string_type to_string)
{
	object_t *object = malloc(sizeof *object);

	object->default_constructor = default_constructor ? default_constructor : shallow_default_constructor;
	object->copy_constructor = copy_constructor ? copy_constructor : shallow_copy_constructor;
	object->destructor = destructor ? destructor : shallow_destructor;
	object->to_string = to_string ? to_string : empty_string;
	object->elem = elem ? object->default_constructor() : object->copy_constructor(elem);

	return object;
}

void *object_default_constructor()
{
	return object_constructor(NULL, shallow_default_constructor,
			shallow_copy_constructor,
			shallow_destructor,
			empty_string);
}

void *object_copy_constructor(void *elem)
{
	if (!elem)
	{
		return NULL;
	}

	object_t *object = (object_t *)elem;
	object_t *new_object = malloc(sizeof *new_object);
	memcpy(new_object, object, sizeof *object);
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


