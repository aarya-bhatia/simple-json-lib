#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "json.h"

int main(int argc, char *argv[])
{
	// json_array_t *array = json_array_create();
	json_object_t *json = json_object_create();

	json_base_t *string_base1 = json_base_create();
	string_base1->type = json_type_string;

	json_base_t *string_base2 = json_base_clone(string_base1);

	string_base1->value = json_string_create();
	((json_string_t *)string_base1->value)->string = strdup("Hello");

	string_base2->value = json_string_create();
	((json_string_t *)string_base2->value)->string = strdup("World");

	json_object_set(json, "Hello", string_base1);
	json_object_set(json, "World", string_base2);

	String *s = json_object_to_string(json);
	char *cstr = StringToCstr(s);
	puts(cstr);

	json_object_free(json);

	return 0;
}
