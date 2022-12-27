// #include <stdlib.h>
// #include <stdio.h>
// #include <assert.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdbool.h>

// #include "json.h"


// json_base_t *json_base_create(json_type type, void *value)
// {
// 	json_base_t *base = malloc(sizeof *base);
// 	base->type = type;
// 	base->value = value;
// 	return base;
// }

// json_object_t *json_object_create()
// {
// 	return calloc(sizeof(json_object_t), 1);
// }

// json_object_t *json_object_clone(json_object_t *json)
// {
// 	assert(json);

// 	json_object_t *other = json_object_create();
// 	other->key = json->key ? strdup(json->key) : NULL;
// 	other->value = json->value ? json_base_clone(json->value) : NULL;
// 	other->next = json->next ? json_object_clone(json->next) : NULL;
// 	return other;
// }

// void json_object_free(json_object_t *json)
// {
// 	if (!json)
// 	{
// 		return;
// 	}

// 	free(json->key);

// 	json_base_free(json->value);

// 	free(json);
// }

// String *json_object_to_string(json_object_t *json)
// {
// 	assert(json);

// 	String *s = StringConstructor(0);
// 	StringAdd(s, '{');

// 	for (json_object_t *itr = json; itr; itr = itr->next)
// 	{
// 		if (!itr->key)
// 		{
// 			break;
// 		}

// 		String *s_key = CstrToString(itr->key);

// 		StringAdd(s, '"');
// 		StringAppend(s, s_key);
// 		StringAdd(s, '"');

// 		StringAdd(s, ':');
// 		StringAdd(s, ' ');

// 		StringDestructor(s_key);

// 		String *s_val = json_base_to_string(itr->value);

// 		StringAppend(s, s_val);

// 		if (itr->next)
// 		{
// 			StringAdd(s, ',');
// 		}

// 		StringDestructor(s_val);
// 	}

// 	StringAdd(s, '}');

// 	return s;
// }

// json_array_t *json_array_create()
// {
// 	return calloc(sizeof(json_array_t), 1);
// }

// json_array_t *json_array_clone(json_array_t *json)
// {
// 	assert(json);

// 	json_array_t *other = json_array_create();
// 	other->value = json->value ? json_base_clone(json->value) : NULL;
// 	other->next = json->next ? json_array_clone(json->next) : NULL;
// 	return other;
// }

// void json_array_free(json_array_t *json)
// {
// 	if (!json)
// 	{
// 		return;
// 	}

// 	json_base_free(json->value);

// 	free(json);
// }

// String *json_array_to_string(json_array_t *json)
// {
// 	assert(json);

// 	String *s = StringConstructor(0);
// 	StringAdd(s, '[');

// 	for (json_array_t *itr = json; itr; itr = itr->next)
// 	{
// 		if (!itr->value)
// 		{
// 			break;
// 		}

// 		String *s1 = json_base_to_string(itr->value);

// 		StringAppend(s, s1);

// 		if (itr->next)
// 		{
// 			StringAdd(s, ',');
// 		}

// 		StringDestructor(s1);
// 	}

// 	StringAdd(s, ']');

// 	return s;
// }

// json_string_t *json_string_create(const char *string)
// {
// 	assert(string);
// 	json_string_t *json = malloc(sizeof *json);
// 	json->string = strdup(string);
// 	return json;
// }

// json_string_t *json_string_clone(json_string_t *json)
// {
// 	assert(json);
// 	return json_string_create(json->string);
// }

// void json_string_free(json_string_t *json)
// {
// 	if (!json)
// 	{
// 		return;
// 	}

// 	free(json->string);
// 	free(json);
// }

// String *json_string_to_string(json_string_t *json)
// {
// 	assert(json);

// 	String *result = StringConstructor(0);
// 	StringAdd(result, '"');
// 	String *content = CstrToString(json->string);
// 	StringAppend(result, content);
// 	StringAdd(result, '"');
// 	StringDestructor(content);

// 	return result;
// }

// json_number_t *json_number_create(double number)
// {
// 	json_number_t *json = malloc(sizeof *json);
// 	json->number = number;
// 	return json;
// }

// json_number_t *json_number_clone(json_number_t *json)
// {
// 	assert(json);
// 	return json_number_create(json->number);
// }

// void json_number_free(json_number_t *json)
// {
// 	if (!json)
// 	{
// 		return;
// 	}

// 	free(json);
// }

// String *json_number_to_string(json_number_t *json)
// {
// 	assert(json);

// 	char *numStr;
// 	asprintf(&numStr, "%f", json->number);
// 	String *s = CstrToString(numStr);
// 	free(numStr);
// 	return s;
// }

// json_boolean_t *json_boolean_create(char boolean)
// {
// 	json_boolean_t *json = malloc(sizeof *json);
// 	json->boolean = boolean;
// 	return json;
// }

// json_boolean_t *json_boolean_clone(json_boolean_t *json)
// {
// 	assert(json);
// 	return json_boolean_create(json->boolean);
// }

// void json_boolean_free(json_boolean_t *json)
// {
// 	if (!json)
// 	{
// 		return;
// 	}

// 	free(json);
// }

// String *json_boolean_to_string(json_boolean_t *json)
// {
// 	assert(json);

// 	return CstrToString(json->boolean ? "true" : "false");
// }

// json_base_t *json_object_get(json_object_t *json, const char *key)
// {
// 	json_object_t *itr = NULL;

// 	json_object_iterator(json, itr, {
// 		if (itr->key && !strcmp(itr->key, key))
// 		{
// 			return itr->value;
// 		}
// 	});

// 	return NULL;
// }

// // TODO
// json_object_t *json_object_emplace(json_object_t *json, const char *key, json_type type, void *value)
// {
// 	return NULL;
// }

// json_object_t *json_object_set(json_object_t *json, const char *key, json_base_t *value)
// {
// 	json_object_t *itr = NULL;

// 	json_object_iterator(json, itr, {
// 		if (itr->key && !strcmp(itr->key, key))
// 		{
// 			if (itr->value)
// 			{
// 				json_base_free(itr->value);
// 			}

// 			itr->value = json_base_clone(value);
// 			return json;
// 		}
// 	});

// 	json_object_t *new_json = json_object_create();
// 	new_json->key = strdup(key);
// 	new_json->value = json_base_clone(value);
// 	new_json->next = json;

// 	return new_json;
// }

// json_base_t *json_array_get(json_array_t *json, size_t index)
// {
// 	assert(json);

// 	if (index == 0)
// 	{
// 		return json->value;
// 	}

// 	json_array_t *itr = json;

// 	for (size_t i = 0; i < index; i++)
// 	{
// 		if (!itr)
// 		{
// 			break;
// 		}

// 		itr = itr->next;
// 	}
// 	return NULL;
// }

// json_array_t *json_array_add(json_array_t *json, json_base_t *value)
// {
// 	json_array_t *new_json = json_array_create();
// 	new_json->next = json;
// 	new_json->value = json_base_clone(value);
// 	return new_json;
// }

// // char *json_string_get(json_string_t *json);
// // void json_string_set(json_string_t *json, const char *content);

// // double json_number_get(json_number_t *json);
// // void json_number_set(json_number_t *json, double new_number);

// // char json_boolean_get(json_boolean_t *json);
// // void json_boolean_set(json_boolean_t *json, char new_boolean);