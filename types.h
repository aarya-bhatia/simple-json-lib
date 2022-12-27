#pragma once

typedef void *(*default_constructor_type)();
typedef void (*destructor_type)(void *);
typedef void *(*copy_constructor_type)(void *);

typedef struct object_t
{
    void *elem;
    copy_constructor_type copy_constructor;
    destructor_type destructor;
} object_t;

void *shallow_default_constructor();
void shallow_destructor(void *elem);
void *shallow_copy_constructor();

void *null_default_constructor();
void *null_copy_constructor(void *elem);
void null_destructor(void *elem);

void *object_constructor(copy_constructor_type copy_constructor,
                         destructor_type destructor);

void *object_default_constructor();
void *object_copy_constructor(void *elem);
void object_destructor(void *elem);

void *string_default_constructor();
void *string_copy_constructor(void *elem);
void string_destructor(void *elem);

void *number_default_constructor();
void *number_copy_constructor(void *elem);
void number_destructor(void *elem);

void *boolean_default_constructor();
void *boolean_copy_constructor(void *elem);
void boolean_destructor(void *elem);
