#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "sstring.h"
#include "common.h"

void json_free(json_t *json) {
	if(!json) { return;}

	if(json->type==json_type_object){
		json_object_free(json);
	}

	else if(json->type==json_type_array){
		json_array_free(json);
	}

	else if(json->type==json_type_string){
		json_string_free(json);
	}
}

void json_string_free(json_t *json) {
	if(!json) {return;}
	free(json->value);
	free(json);
}

void json_array_free(json_t *json) {
	if(!json) {return;}
	json_array_t *array = json->value;
	json_free(array->value);
	json_array_free(array->next);
	free(json);
}

void json_object_free(json_t *json) {
	if(!json) {return;}
	json_array_t *obj = json->value;
	free(obj->key);
	json_free(obj->value);
	json_object_free(obj->next);
	free(json);
}

json_t *json_create() {
	return calloc(1, sizeof *json);
}

json_t *json_empty() {
	return NULL;
}

json_t *json_string_create(char *content) {
	json_t *json = json_create();
	json->type = json_type_string;
	json->value = strdup(content);
	return json;
}

json_t *json_array_create() {
	json_t *json = json_create();
	json->type = json_type_array;
	json->value = calloc(1, sizeof(json_array_t));
	return json;
}

json_t *json_object_create() {
	json_t *json = json_create();
	json->type = json_type_object;
	json->value = calloc(1, sizeof(json_object_t));
	return json;
}

json_t *json_clone(json_t *json) {
	if(json->json_type == json_type_null){
		return json_create();
	}

	if(json->json_type == json_type_object) {
		return json_object_clone(json);
	}

	if(json->json_type == json_type_array) {
		return json_array_clone(json);
	}

	if(json->json_type == json_type_string) {
		return json_string_clone(json);
	}
	
	return NULL;
}


json_t *json_string_clone(json_t *json) {
	assert(json);
	assert(json->type == json_type_string);

	json *copy = json_create();
	copy->json_type = json_type_string;
	copy->value = strdup(json->value);
	
	return copy;
}


json_t *json_array_clone(json_t *json);
json_t *json_object_clone(json_t *json);


void json_object_set(json_t *json, char *key, json_t *value);
json_t *json_object_get(json_t *json, char *key);

void json_array_get(json_t *json, size_t index);
void json_array_add(json_t *json, json_t *entry);
void json_array_remove(json_t *json, size_t index);

