#include "Aarya/ht.h"
#include "callbacks.h"
#include "compare.h"
#include <assert.h>

int main()
{
    ht_t h;

    ht_init(&h, string_hash_function, string_compare, string_copy_constructor, string_destructor, string_to_string, int_copy_constructor, int_destructor, int_to_string);

    int b = 1, a = 2, o = 3;

    LOG("Adding banana -> %d", b);
    ht_set(&h, "Banana", &b);

    LOG("Adding apple -> %d", a);
    ht_set(&h, "Apple", &a);

    LOG("Adding orange -> %d", o);
    ht_set(&h, "Orange", &o);

    LOG("Adding orange -> %d", a);
    ht_set(&h, "Orange", &a);

    assert(*(int *)ht_get(&h, "Banana") == b);
    assert(*(int *)ht_get(&h, "Apple") == a);
    assert(*(int *)ht_get(&h, "Orange") == a);
    assert(!ht_get(&h, "Pomegranate"));

	char *ht_str = ht_to_string((void *)&h);
	puts(ht_str);
	free(ht_str);

    ht_destroy(&h);

    return 0;
}
