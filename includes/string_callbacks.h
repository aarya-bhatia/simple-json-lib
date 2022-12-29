#pragma once

typedef char *(*to_string_type)(void *);

char *null_to_string(void *elem);
char *string_to_string(void *elem);
char *int_to_string(void *elem);
char *float_to_string(void *elem);
char *double_to_string(void *elem);
char *boolean_to_string(void *elem);
