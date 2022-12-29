#include "Aarya/ht.h"
#include "Aarya/String.h"

ht_node_t *ht_find(ht_t *ht, void *key);
ht_node_t *ht_node_clone(const ht_t *table, const ht_node_t *node);
int string_compare(void *a, void *b);

int string_compare(void *a, void *b)
{
    return strcmp(a, b);
}

void ht_init(ht_t *ht,
             hash_function_type hash_function,
             compare key_comparator,
             copy_constructor_type key_copy_constructor,
             destructor_type key_destructor,
			 to_string_type key_to_string,
             copy_constructor_type value_copy_constructor,
             destructor_type value_destructor,
			 to_string_type value_to_string)
{
    assert(ht);
    assert(hash_function);
    assert(key_comparator);
    assert(key_copy_constructor);
    assert(key_destructor);
    assert(value_copy_constructor);
    assert(value_destructor);

    ht->capacity = HT_INITIAL_CAPACITY;
    ht->table = calloc(HT_INITIAL_CAPACITY, sizeof(ht_node_t *));
    ht->size = 0;

    ht->hash_function = hash_function;
    ht->key_comparator = key_comparator;
    ht->key_copy_constructor = key_copy_constructor;
    ht->key_to_string = key_to_string;
    ht->key_destructor = key_destructor;
    ht->value_copy_constructor = value_copy_constructor;
    ht->value_destructor = value_destructor;
	ht->value_to_string = value_to_string;
    LOG("hash table initialized");
}

ht_node_t *ht_find(ht_t *ht, void *key)
{
    assert(ht);
    assert(key);

    size_t hash = ht->hash_function(key) % ht->capacity;
    LOG("hash=%zu", hash);

    ht_node_t *node = ht->table[hash];

    while (node)
    {
        if (ht->key_comparator(node->key, key) == 0)
        {
            return node;
        }
        node = node->next;
    }

    LOG("key not found");

    return NULL;
}

void ht_set(ht_t *ht, void *key, void *value)
{
    assert(ht);
    assert(key);

    ht_node_t *found = ht_find(ht, key);

    if (found)
    {
        LOG("key found");
        ht->value_destructor(found->value);
        found->value = ht->value_copy_constructor(value);
    }
    else
    {
        size_t hash = (ht->hash_function(key)) % ht->capacity;
        LOG("hash=%zu", hash);
        ht_node_t *new_node = malloc(sizeof *new_node);
        new_node->key = ht->key_copy_constructor(key);
        new_node->value = ht->value_copy_constructor(value);
        new_node->next = ht->table[hash];
        LOG("adding new node");
        ht->table[hash] = new_node;
        ht->size++;
    }

    LOG("table size=%zu, capacity=%zu", ht->size, ht->capacity);

    if (ht->size / ht->capacity > HT_DENSITY)
    {
        // Rehash
        LOG("Rehashing...");
        size_t new_capacity = (ht->capacity * 2) + 1;
        ht_node_t **new_table = malloc(sizeof(ht_node_t *) * new_capacity);

        for (size_t i = 0; i < ht->capacity; i++)
        {
            if (ht->table[i])
            {
                size_t new_hash = ht->hash_function(ht->table[i]->key) % new_capacity;
                new_table[new_hash] = ht->table[i];
            }
        }

        free(ht->table);
        ht->table = new_table;
        ht->capacity = new_capacity;
    }
}

void *ht_get(ht_t *ht, void *key)
{
    assert(ht);
    assert(key);

    size_t hash = ht->hash_function(key) % ht->capacity;
    LOG("hash=%zu", hash);

    ht_node_t *node = ht->table[hash];

    while (node)
    {
        if (ht->key_comparator(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }

    LOG("key not found");

    return NULL;
}

void ht_destroy(ht_t *ht)
{
    if (!ht)
    {
        return;
    }
    for (size_t i = 0; i < ht->capacity; i++)
    {
        if (ht->table[i])
        {
            ht_node_t *itr = ht->table[i];

            while (itr)
            {
                ht->key_destructor(itr->key);
                ht->value_destructor(itr->value);
                ht_node_t *tmp = itr->next;
                free(itr);
                itr = tmp;
            }
        }
    }

    free(ht->table);
    LOG("hash table destroyed");
}

ht_node_t *ht_node_clone(const ht_t *table, const ht_node_t *node)
{
    if (!node)
    {
        return NULL;
    }

    ht_node_t *new_node = malloc(sizeof *new_node);
    new_node->key = table->key_copy_constructor(node->key);
    new_node->value = table->value_copy_constructor(node->value);
    new_node->next = ht_node_clone(table, node->next);

    return new_node;
}

void *ht_copy_constructor(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    ht_t *table = (ht_t *)elem;
    ht_t *new_table = malloc(sizeof *new_table);

    new_table->size = table->size;
    new_table->capacity = table->capacity;
    new_table->hash_function = table->hash_function;
    new_table->key_comparator = table->key_comparator;
    new_table->key_copy_constructor = table->key_copy_constructor;
    new_table->key_to_string = table->key_to_string;
    new_table->key_destructor = table->key_destructor;
    new_table->value_copy_constructor = table->value_copy_constructor;
    new_table->value_destructor = table->value_destructor;
    new_table->value_to_string = table->value_to_string;

    new_table->table = calloc(table->capacity, sizeof(ht_node_t *));

    for (size_t i = 0; i < table->capacity; i++)
    {
        new_table->table[i] = ht_node_clone(table, table->table[i]);
    }

    return new_table;
}

void ht_destructor(void *elem)
{
    if (!elem)
    {
        return;
    }

    ht_destroy((ht_t *)elem);
}

char *ht_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    ht_t *ht = (ht_t *)elem;
    size_t c = 0;

    String *s = StringDefaultConstructor();
    StringAdd(s, '{');

    for (size_t i = 0; i < ht->capacity; i++)
    {
        if (!ht->table[i])
        {
            continue;
        }

        ht_node_t *node = ht->table[i];

        while (node)
        {
            assert(node->key);
            assert(node->value);

            char *key_str = ht->key_to_string(node->key);
			StringAddCstr(s, key_str);
            free(key_str);

			StringAdd(s, ':');
			StringAdd(s, ' ');

            char *value_str = ht->value_to_string(node->value);
			StringAddCstr(s, value_str);
            free(value_str);

            if (c < ht->size)
            {
                StringAdd(s, ',');
                StringAdd(s, ' ');
                c++;
            }

            node = node->next;
        }
    }

    StringAdd(s, '}');

    char *sstr = StringToCstr(s);
    StringDestructor(s);
    return sstr;
}
