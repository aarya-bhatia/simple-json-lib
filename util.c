#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "json.h"

json_t *wrap_json_object(json_object_t *object)
{
	json_t *json = json_create();
	json->type = json_type_object;
	json->value = object;
	return json;
}

json_t *wrap_json_array(json_array_t *array)
{
	json_t *json = json_create();
	json->type = json_type_array;
	json->value = array;
	return json;
}

json_t *json_from(void *value, json_type type, int shallow)
{
	json_t *json = json_create();
	json->type = type;

	if (shallow)
	{
		json->value = value;
	}
	else
	{
		switch (json->type)
		{
		case json_type_null:
			json->value = NULL;
			break;

		case json_type_string:
			json->value = strdup((char *)value);
			break;

		case json_type_object:
			json->value = json_object_clone((json_object_t *)value);
			break;

		case json_type_array:
			json->value = json_array_clone((json_array_t *)value);
			break;

		default:
			abort();
			break;
		}
	}

	return json;
}
