
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "sstring.h"
#include "util.h"

int main(int argc, char *argv[])
{
	// data = { A: { B: "1" }, C: "2", D: [], E: null  }
	
	json_t *json_a = wrap_json_object(json_object_create());
	json_t *json_b = wrap_json_object(json_object_create());
	json_t *json_b_val = json_from("1", json_type_string, false);

	json_object_set( (json_object_t *) json_a->value, "A", json_b, true );
	json_object_set( (json_object_t *) json_b->value, "B", json_b_val, true );

	char *s = json_to_string(json_a);
	puts(s);
	free(s);

	json_free(json_a);

	return 0;
}
