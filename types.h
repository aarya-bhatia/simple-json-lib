#pragma once

typedef void *(*default_constructor_type)();
typedef void (*destructor_type)(void *);
typedef void *(*copy_constructor_type)(void *);
typedef char *(*to_string_type)(void *);

typedef struct object_t
{
    void *elem;
    copy_constructor_type copy_constructor;
    destructor_type destructor;
    to_string_type to_string;
} object_t;

#define string_object() object_constructor(string_copy_constructor, string_destructor, string_to_string)

#define number_object() object_constructor(number_copy_constructor, number_destructor, number_to_string)

#define boolean_object() object_constructor(boolean_copy_constructor, boolean_destructor, boolean_to_string)

#define shallow_object() object_constructor(shallow_copy_constructor, shallow_destructor, shallow_to_string)


void *shallow_default_constructor();
void shallow_destructor(void *elem);
void *shallow_copy_constructor(void *elem);
char *shallow_to_string(void *elem);

void *null_default_constructor();
void *null_copy_constructor(void *elem);
void null_destructor(void *elem);
char *null_to_string(void *elem);

void object_set(object_t *object, void *elem);
void *object_get(object_t *object);

void *object_constructor(copy_constructor_type copy_constructor,
                         destructor_type destructor,
                         to_string_type to_string);

void *object_default_constructor();
void *object_copy_constructor(void *elem);
void object_destructor(void *elem);
char *object_to_string(void *elem);

void *string_default_constructor();
void *string_constructor(char*str);
void *string_copy_constructor(void *elem);
void string_destructor(void *elem);
char *string_to_string(void *elem);

void *number_default_constructor();
void *number_copy_constructor(void *elem);
void number_destructor(void *elem);
char *number_to_string(void *elem);

void *boolean_default_constructor();
void *boolean_copy_constructor(void *elem);
void boolean_destructor(void *elem);
char *boolean_to_string(void *elem);
