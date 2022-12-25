#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"

json_base_t *json_base_create()
{
	return calloc(1, sizeof(json_base_t));
}

json_base_t *json_base_clone(json_base_t *json)
{
	json_base_t *base = json_base_create();
	base->type = json->type;

	switch (json->type)
	{
	case json_type_boolean:
		base->value = json_boolean_clone(json->value);
		break;
	case json_type_array:
		base->value = json_array_clone(json->value);
		break;
	case json_type_object:
		base->value = json_object_clone(json->value);
		break;
	case json_type_number:
		base->value = json_number_clone(json->value);
		break;
	case json_type_string:
		base->value = json_string_clone(json->value);
		break;
	default:
		base->value = NULL;
		break;
	}

	return base;
}

String *json_base_to_string(json_base_t *json)
{
	switch (json->type)
	{
	case json_type_null:
		return CstrToString("null");
	case json_type_boolean:
		return json_boolean_to_string(json->value);
	case json_type_array:
		return json_array_to_string(json->value);
	case json_type_object:
		return json_object_to_string(json->value);
	case json_type_number:
		return json_number_to_string(json->value);
	case json_type_string:
		return json_string_to_string(json->value);
	default:
		LOG("undefined type");
		return NULL;
	}
}

void json_base_free(json_base_t *json)
{
	if (!json)
	{
		return;
	}

	switch (json->type)
	{
	case json_type_boolean:
		break;
	case json_type_array:
		json_array_free(json->value);
		break;
	case json_type_object:
		json_object_free(json->value);
		break;
	case json_type_number:
		json_number_free(json->value);
		break;
	case json_type_string:
		json_string_free(json->value);
		break;
	default:
		break;
	}

	free(json);
}

json_object_t *json_object_create()
{
	return calloc(sizeof(json_object_t), 1);
}

// TODO
json_object_t *json_object_clone(json_object_t *json)
{
	return NULL;
}

void json_object_free(json_object_t *json)
{
	if (!json)
	{
		return;
	}

	free(json->key);

	json_base_free(json->value);

	free(json);
}

// TODO
String *json_object_to_string(json_object_t *json)
{
	assert(json);
	return NULL;
}

json_array_t *json_array_create()
{
	return calloc(sizeof(json_array_t), 1);
}

// TODO
json_array_t *json_array_clone(json_array_t *json)
{
	assert(json);
	return NULL;
}

void json_array_free(json_array_t *json)
{
	if (!json)
	{
		return;
	}

	json_base_free(json->value);

	free(json);
}

// TODO
String *json_array_to_string(json_array_t *json)
{
	assert(json);
	return NULL;
}

json_string_t *json_string_create()
{
	return calloc(sizeof(json_string_t), 1);
}

json_string_t *json_string_clone(json_string_t *json)
{
	assert(json);
	json_string_t *other = json_string_create();
	other->string = strdup(json->string);
	return other;
}

void json_string_free(json_string_t *json)
{
	if (!json)
	{
		return;
	}

	free(json->string);
	free(json);
}

String *json_string_to_string(json_string_t *json)
{
	assert(json);

	return CstrToString(json->string);
}

json_number_t *json_number_create()
{
	return calloc(sizeof(json_number_t), 1);
}

json_number_t *json_number_clone(json_number_t *json)
{
	assert(json);
	json_number_t *other = json_number_create();
	other->number = json->number;
	return other;
}

void json_number_free(json_number_t *json)
{
	if (!json)
	{
		return;
	}

	free(json);
}

String *json_number_to_string(json_number_t *json)
{
	assert(json);

	char *numStr;
	asprintf(&numStr, "%f", json->number);
	String *s = CstrToString(numStr);
	free(numStr);
	return s;
}

json_boolean_t *json_boolean_create()
{
	return calloc(sizeof(json_boolean_t), 1);
}

json_boolean_t *json_boolean_clone(json_boolean_t *json)
{
	assert(json);
	json_boolean_t *other = json_boolean_create();
	other->boolean = json->boolean;
	return other;
}

void json_boolean_free(json_boolean_t *json)
{
	if (!json)
	{
		return;
	}

	free(json);
}

String *json_boolean_to_string(json_boolean_t *json)
{
	assert(json);

	return CstrToString(json->boolean ? "true" : "false");
}

/**
String *json_to_string(json_base_t *json)
{
	if (!json || json->type == json_type_null)
	{
		return calloc(1, 1); // empty string
	}
	else if (json->type == json_type_string)
	{
		return strdup((const char *)json->value);
	}

	String *s = StringConstructor(0);

	if (json->type == json_type_array)
	{
		StringAdd(s, '[');

		for (json_array_t *obj = json->value; obj; obj = obj->next)
		{
			if (!obj->value)
			{
				break;
			}

			char *value_str = json_to_string(obj->value);

			String *tmp = CstrToString(value_str);
			StringAppend(s, tmp);
			StringDestructor(tmp);

			free(value_str);

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

			String *tmp = CstrToString(s1);
			StringAppend(s, tmp);
			StringDestructor(tmp);

			free(value_str);
			free(s1);

			if (obj->next)
			{
				sstring_putc(s, ',');
			}
		}

		StringAdd(s, '}');
	}

	char *cstr = StringToCstr(s);
	StringDestructor(s);
	return cstr;
}
*/
