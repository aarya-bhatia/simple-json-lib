#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "json.h"

int main()
{
	json_object_t *json = json_object_create();

	json = json_object_set(json, "Hello", json_string("Hello"));
	json = json_object_set(json, "World", json_string("World"));

	String *s = json_object_to_string(json);
	StringWrite(s, 1);
	StringDestructor(s);

	json_object_free(json);

	return 0;
}
