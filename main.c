
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "sstring.h"

int main(int argc, char *argv[])
{
	// data = { A: { B: "1" }, C: "2", D: [], E: null  }
	
	json_t *json_a = json_create();
	json_a->type = json_type_object;
	json_a->value = json_object_create();

	json_t *json_b = json_create();
	json_b->type = json_type_object;
	json_b->value = json_object_create();

	json_t *json_b_val = json_create();
	json_b_val->type = json_type_string;
	json_b_val->value = strdup("1");

	json_object_set( (json_object_t *) json_a->value, "A", json_b, true );
	json_object_set( (json_object_t *) json_b->value, "B", json_b_val, true );

	json_free(json_a);

	return 0;
}
