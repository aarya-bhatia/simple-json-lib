#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"

void json_free(json_t *json)
{
	if (!json)
	{
		return;
	}

	if (json->type == json_type_null)
	{
		assert(json->value == NULL);
	}

	else if (json->type == json_type_object)
	{
		json_object_free(json->value);
	}

	else if (json->type == json_type_array)
	{
		json_array_free(json->value);
	}

	else if (json->type == json_type_string)
	{
		free(json->value);
	}

	free(json);
}

void json_array_free(json_array_t *array)
{
	if (!array)
	{
		return;
	}

	json_free(array->value);
	json_array_free(array->next);

	free(array);
}

void json_object_free(json_object_t *obj)
{
	if (!obj)
	{
		return;
	}

	free(obj->key);
	json_free(obj->value);
	json_object_free(obj->next);

	free(obj);
}

json_t *json_create()
{
	return calloc(1, sizeof(json_t));
}

json_array_t *json_array_create()
{
	return calloc(1, sizeof(json_array_t));
}

json_object_t *json_object_create()
{
	return calloc(1, sizeof(json_object_t));
}

json_t *json_clone(json_t *json)
{
	if (!json)
	{
		return NULL;
	}

	json_t *new_json = json_create();
	new_json->type = json->type;

	if (json->type == json_type_null)
	{
		new_json->value = NULL;
	}
	else if (json->type == json_type_object)
	{
		new_json->value = json_object_clone(json->value);
	}
	else if (json->type == json_type_array)
	{
		new_json->value = json_array_clone(json->value);
	}
	else if (json->type == json_type_string)
	{
		new_json->value = strdup(json->value);
	}

	return new_json;
}

json_array_t *json_array_clone(json_array_t *array)
{
	if (!array)
	{
		return NULL;
	}

	json_array_t *new_array = calloc(1, sizeof *new_array);
	new_array->value = json_clone(array->value);
	new_array->next = json_array_clone(array->next);

	return new_array;
}

json_object_t *json_object_clone(json_object_t *obj)
{
	if (!obj)
	{
		return NULL;
	}

	json_object_t *new_obj = calloc(1, sizeof *new_obj);
	new_obj->key = strdup(obj->key);
	new_obj->value = json_clone(obj->value);
	new_obj->next = json_object_clone(obj->next);

	return new_obj;
}

/**
 * Find the value associated with the given key from the json object type
 */
json_t *json_object_get(json_object_t *obj, const char *key)
{
	while (obj)
	{
		if (obj->key && !strcmp(obj->key, key))
		{
			return obj->value;
		}

		obj = obj->next;
	}
	return NULL;
}

void json_object_set(json_object_t *obj, const char *key, json_t *value, bool shallow_copy)
{
	// object is empty
	if (!obj->key && !obj->value)
	{
		obj->key = strdup(key);
		obj->value = shallow_copy ? value : json_clone(value);
		return;
	}

	// check key exists
	json_t *found = json_object_get(obj, key);

	// remove old and copy new value
	if (found)
	{
		json_free(found->value);
		found->value = shallow_copy ? value : json_clone(value);
	}
	else
	{
		// create new obj
		json_object_t *new_obj = json_object_create();
		new_obj->key = strdup(key);
		new_obj->value = shallow_copy ? value : json_clone(value);

		// add new obj to current obj's list
		new_obj->next = obj;
		obj->next = new_obj;
	}
}

// void json_array_get(json_t *json, size_t index);
// void json_array_add(json_t *json, json_t *entry);
// void json_array_remove(json_t *json, size_t index);

char *json_to_string(json_t *json)
{
	if (!json || json->type == json_type_null)
	{
		return calloc(1, 1); // empty string
	}
	else if (json->type == json_type_string)
	{
		return strdup((const char *)json->value);
	}

	sstring *s = sstring_default_constructor();

	if (json->type == json_type_array)
	{
		sstring_putc(s, '[');

		for (json_array_t *obj = json->value; obj; obj = obj->next)
		{
			if (!obj->value)
			{
				break;
			}

			char *value_str = json_to_string(obj->value);

			sstring *tmp = cstr_to_sstring(value_str);
			sstring_append(s, tmp);
			sstring_destroy(tmp);

			if (obj->next)
			{
				sstring_putc(s, ',');
			}
		}

		sstring_putc(s, ']');
	}
	else if (json->type == json_type_object)
	{
		sstring_putc(s, '{');

		for (json_object_t *obj = json->value; obj; obj = obj->next)
		{
			if (!obj->key)
			{
				break;
			}

			char *value_str = json_to_string(obj->value);

			char *s1;
			asprintf(&s1, "\"%s\": %s", obj->key, value_str);

			sstring *tmp = cstr_to_sstring(s1);
			sstring_append(s, tmp);
			sstring_destroy(tmp);

			free(s1);

			if (obj->next)
			{
				sstring_putc(s, ',');
			}
		}

		sstring_putc(s, '}');
	}

	char *cstr = sstring_to_cstr(s);
	sstring_destroy(s);
	return cstr;
}
