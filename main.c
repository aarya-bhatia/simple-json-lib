#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "json.h"

int main()
{
	json_object_t *json = json_object_constructor(
		json_object_copy_constructor,
		json_object_destructor,
		json_object_to_string);

	json_object_t *json1 = json_object_constructor(
		string_copy_constructor,
		string_destructor,
		string_to_string);

	json_object_t *json2 = json_object_constructor(
		number_copy_constructor,
		number_destructor,
		number_to_string);

	json1->key = strdup("json_1");
	json2->key = strdup("json_2");

	object_set(json1->value, "hello");
	object_set(json2->value, (double[]){1});

	json1->next = json2;

	// json->key = strdup("json");
	// json_object_set_value(json, json1);
	// puts(json_object_to_string(json));

	char *s = json_object_to_string(json1);
	puts(s);
	free(s);

	json_object_destructor(json1);
	json_object_destructor(json);

	return 0;
}
