
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
	
	json_t *data = json_object_create();

	json_object_set(data, "A", json_object_create());
	json_object_set( json_object_get(data, "A"), "B", json_string_create("1") );
	json_object_set(data, "C", json_string_create("2"));
	json_object_set(data, "D", json_array_create());
	json_object_set(data, "E", NULL);

	return 0;
}
