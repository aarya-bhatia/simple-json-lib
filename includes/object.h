#pragma once

#include "common.h"

typedef struct object_t
{
	void *elem;
	default_constructor_type default_constructor;
	copy_constructor_type copy_constructor;
	destructor_type destructor;
	to_string_type to_string;
} object_t;

void *object_constructor(void *elem, 
		default_constructor_type default_constructor,
		copy_constructor_type copy_constructor,
		destructor_type destructor,
		to_string_type to_string);

void *object_default_constructor(void);
void *object_copy_constructor(void *elem);
void object_destructor(void *elem);
char *object_to_string(void *elem);

void object_set(object_t *object, void *elem);
void *object_get(object_t *object);
