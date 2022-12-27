#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "json.h"

int main()
{
	json_object_t *json = json_string_object();
	json_object_set_key(json, "hello");
	json_object_set_value(json, "world");
	puts(json_object_to_string(json));
	json_object_destructor(json);

	return 0;
}
