#pragma once

#include "json.h"

json_t *wrap_json_object(json_object_t *object);
json_t *wrap_json_array(json_array_t *array);
json_t *json_from(void *value, json_type type, int shallow);
