#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "StringLibrary.h"

void check_string(String *s, char *value, size_t size)
{
	assert(s);
	assert(!memcmp(s->buffer, value, size));
	assert(StringSize(s) == size);
	assert(StringCapacity(s) >= StringSize(s));
}

void check_string_append(char *s1, char *s2)
{
	String *t1 = CstrToString(s1);
	String *t2 = CstrToString(s2);

	assert(t1);
	assert(t2);

	size_t l1 = strlen(s1), l2 = strlen(s2);

	StringAppend(t1, t2);

	assert(!memcmp(t1->buffer, s1, l1));
	assert(!memcmp(t2->buffer, s2, l2));
	assert(!memcmp(t1->buffer + l1, s2, l2));

	assert(t1->size == l1 + l2);

	assert(t1->capacity >= t1->size);
	assert(t2->capacity >= t2->size);

	StringDestructor(t1);
	StringDestructor(t2);
}

int main()
{
	String *s = StringDefaultConstructor();
	check_string(s, "", 0);
	assert(s->capacity == INITIAL_CAPACITY);

	String *s1 = CstrToString("aarya");
	check_string(s1, "aarya", 5);

	char *c2 = StringSlice(s1, 1, 3);
	String *s2 = CstrToString(c2);
	free(c2);
	check_string(s2, "ar", 2);

	assert(!StringSlice(s1, 1, 0));
	assert(!StringSlice(s1, 6, 7));

	char *c3 = StringSlice(s1, 0, 0);
	String *s3 = CstrToString(c3);
	free(c3);
	check_string(s3, "", 0);

	check_string_append("", "aarya");
	check_string_append("aarya", "");
	check_string_append("aarya", " bhatia");
	check_string_append("", "");

	StringDestructor(s);
	StringDestructor(s1);
	StringDestructor(s2);
	StringDestructor(s3);

	return 0;
}
