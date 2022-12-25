#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "json.h"

int main(int argc, char *argv[])
{
	json_array_t *array = json_array_create();	
	json_string_t *string = json_string_create();
	string->string = strdup("Hello");
	
	return 0;
}
