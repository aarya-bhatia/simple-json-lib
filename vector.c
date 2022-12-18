/**
 * vector
 * CS 341 - Fall 2022
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"
#include "callbacks.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * 'INITIAL_CAPACITY' the initial size of the dynamically.
 */
const size_t INITIAL_CAPACITY = 8;
/**
 * 'GROWTH_FACTOR' is how much the vector will grow by in automatic reallocation
 * (2 means double).
 */
const size_t GROWTH_FACTOR = 2;

struct vector
{
    /* The function callback for the user to define the way they want to copy
     * elements */
    copy_constructor_type copy_constructor;

    /* The function callback for the user to define the way they want to destroy
     * elements */
    destructor_type destructor;

    /* The function callback for the user to define the way they a default
     * element to be constructed */
    default_constructor_type default_constructor;

    /* Void pointer to the beginning of an array of void pointers to arbitrary
     * data. */
    void **array;

    /**
     * The number of elements in the vector.
     * This is the number of actual objects held in the vector,
     * which is not necessarily equal to its capacity.
     */
    size_t size;

    /**
     * The size of the storage space currently allocated for the vector,
     * expressed in terms of elements.
     */
    size_t capacity;
};

void int_vector_print(vector *this)
{
    for (size_t i = 0; i < this->size; i++)
    {
        printf("%d ", *(int *)this->array[i]);
    }
    printf("\n");
}

static size_t get_new_capacity(size_t target);

void vector_print(vector *this, void (*printer)(void *elem))
{
    printf("%p: vector(array: [", (void *) this);

    for (size_t i = 0; i < this->size; i++)
    {
        printf("<");
        (*printer)(vector_get(this, i));
        printf("> ");
    }

    printf("], size: %lu, capacity: %lu)\n", this->size, this->capacity);
}

/* my functions */

void **vector_index(vector *v, size_t i)
{
    assert(v);
    assert(i < v->capacity);
    return &v->array[i];
}

/**
 * IMPLEMENTATION DETAILS
 *
 * The following is documented only in the .c file of vector,
 * since it is implementation specfic and does not concern the user:
 *
 * This vector is defined by the struct above.
 * The struct is complete as is and does not need any modifications.
 *
 * The only conditions of automatic reallocation is that
 * they should happen logarithmically compared to the growth of the size of the
 * vector inorder to achieve amortized constant time complexity for appending to
 * the vector.
 *
 * For our implementation automatic reallocation happens when -and only when-
 * adding to the vector makes its new  size surpass its current vector capacity
 * OR when the user calls on vector_reserve().
 * When this happens the new capacity will be whatever power of the
 * 'GROWTH_FACTOR' greater than or equal to the target capacity.
 * In the case when the new size exceeds the current capacity the target
 * capacity is the new size.
 * In the case when the user calls vector_reserve(n) the target capacity is 'n'
 * itself.
 * We have provided get_new_capacity() to help make this less ambigious.
 */

static size_t get_new_capacity(size_t target)
{
    /**
     * This function works according to 'automatic reallocation'.
     * Start at 1 and keep multiplying by the GROWTH_FACTOR untl
     * you have exceeded or met your target capacity.
     */
    size_t new_capacity = 1;
    while (new_capacity < target)
    {
        new_capacity *= GROWTH_FACTOR;
    }
    return new_capacity;
}

vector *vector_create(copy_constructor_type copy_constructor,
                      destructor_type destructor,
                      default_constructor_type default_constructor)
{

    vector *v = malloc(sizeof(vector));
    assert(v);

    v->copy_constructor = copy_constructor ? copy_constructor : shallow_copy_constructor;
    v->destructor = destructor ? destructor : shallow_destructor;
    v->default_constructor = default_constructor ? default_constructor : shallow_default_constructor;

    v->size = 0;
    v->capacity = INITIAL_CAPACITY;
    v->array = calloc(INITIAL_CAPACITY, sizeof(void *));
    assert(v->array);

    return v;
}

void vector_destroy(vector *this)
{
    assert(this);
    assert(this->array);

    if (this->array)
    {
        for (size_t i = 0; i < this->size; i++)
        {
            (*this->destructor)(this->array[i]);
            this->array[i] = NULL;
        }

        free(this->array);
        this->array = NULL;
    }

    free(this);
}

void **vector_begin(vector *this)
{
    assert(this);
    return this->array + 0;
}

void **vector_end(vector *this)
{
    assert(this);
    return this->array + this->size;
}

size_t vector_size(vector *this)
{
    assert(this);
    return this->size;
}

void vector_resize(vector *this, size_t n)
{
    assert(this);
    assert(n >= 0);

    if (n > this->capacity)
    {
        vector_reserve(this, n);
    }

    /* initialise new elements - if n > size */
    if (n > this->size)
    {
        for (size_t i = this->size; i < n; i++)
        {
            this->array[i] = (*this->default_constructor)();
        }
    }

    /* delete old elements - if n < size */
    if (n < this->size)
    {
        for (size_t i = n; i < this->size; i++)
        {
            (*this->destructor)(this->array[i]);
            this->array[i] = NULL;
        }
    }

    /* set the size */
    this->size = n;
}

size_t vector_capacity(vector *this)
{
    assert(this);
    return this->capacity;
}

bool vector_empty(vector *this)
{
    assert(this);
    return this->size == 0;
}

void vector_reserve(vector *this, size_t n)
{
    assert(this);

    if (n <= this->capacity)
    {
        return;
    }

    size_t new_capacity = get_new_capacity(n);
    this->array = realloc(this->array, new_capacity * sizeof(void *));
    this->capacity = new_capacity;

    assert(this->array);
    assert(new_capacity >= n);
}

void **vector_at(vector *this, size_t position)
{
    assert(this);
    assert(position < vector_size(this));
    return this->array + position;
}

void vector_set(vector *this, size_t position, void *element)
{
    assert(this);
    assert(position < vector_size(this));

    /* Erase element at this position */
    if (this->array[position])
    {
        (*this->destructor)(this->array[position]);
        this->array[position] = NULL;
    }

    /* Set the new element at this position */
    this->array[position] = (*this->copy_constructor)(element);
}

void *vector_get(vector *this, size_t position)
{
    assert(this);
    assert(position < vector_size(this));
    return this->array[position];
}

void **vector_front(vector *this)
{
    assert(this);
    return this->array;
}

void **vector_back(vector *this)
{
    assert(this);
    assert(this->size > 0);
    return this->array + this->size - 1;
}

void vector_push_back(vector *this, void *element)
{
    assert(this);

    if (this->size + 1 >= this->capacity)
    {
        size_t new_capacity = get_new_capacity(this->size + 1);
        this->array = realloc(this->array, new_capacity * sizeof(void *));
        this->capacity = new_capacity;
        assert(this->array);
    }

    void *elem = (*this->copy_constructor)(element);
    this->array[this->size++] = elem;
}

void vector_pop_back(vector *this)
{
    assert(this);
    assert(this->size >= 0);

    /* destroys last element and reduce size by one */

    void *elem = this->array[this->size - 1];
    (*this->destructor)(elem);

    this->array[this->size - 1] = NULL;

    this->size--;
}

void vector_insert(vector *this, size_t position, void *element)
{
    assert(this);
    /** assert(position < this->size); */

    /* when the next element will cause overflow */
    if (this->size + 1 > this->capacity)
    {
        size_t new_capacity = get_new_capacity(this->size + 1);
        this->array = realloc(this->array, new_capacity * sizeof(void *));
        this->capacity = new_capacity;
    }

    assert(this->array);
    assert(this->size + 1 <= this->capacity);

    if (position < this->size)
    {
        memmove(this->array + position + 1, this->array + position, (this->size - position) * sizeof(void *));
    }

    this->array[position] = (*this->copy_constructor)(element);
    this->size++;
}

void vector_erase(vector *this, size_t position)
{
    assert(this);
    assert(this->size > 0);
    assert(position < vector_size(this));
    assert(position >= 0);

    (*this->destructor)(this->array[position]);
    this->array[position] = NULL;

    if (position + 1 < this->size)
    {
        memmove(this->array + position, this->array + position + 1, (this->size - position - 1) * sizeof(void *));
        this->array[this->size - 1] = NULL;
    }

    this->size--;
}

void vector_clear(vector *this)
{
    for (size_t i = 0; i < this->size; i++)
    {
        (*this->destructor)(this->array[i]);
        this->array[i] = NULL;
    }

    this->size = 0;
}

// The following is code generated:
vector *shallow_vector_create()
{
    return vector_create(shallow_copy_constructor, shallow_destructor,
                         shallow_default_constructor);
}
vector *string_vector_create()
{
    return vector_create(string_copy_constructor, string_destructor,
                         string_default_constructor);
}
vector *char_vector_create()
{
    return vector_create(char_copy_constructor, char_destructor,
                         char_default_constructor);
}
vector *double_vector_create()
{
    return vector_create(double_copy_constructor, double_destructor,
                         double_default_constructor);
}
vector *float_vector_create()
{
    return vector_create(float_copy_constructor, float_destructor,
                         float_default_constructor);
}
vector *int_vector_create()
{
    return vector_create(int_copy_constructor, int_destructor,
                         int_default_constructor);
}
vector *long_vector_create()
{
    return vector_create(long_copy_constructor, long_destructor,
                         long_default_constructor);
}
vector *short_vector_create()
{
    return vector_create(short_copy_constructor, short_destructor,
                         short_default_constructor);
}
vector *unsigned_char_vector_create()
{
    return vector_create(unsigned_char_copy_constructor,
                         unsigned_char_destructor,
                         unsigned_char_default_constructor);
}
vector *unsigned_int_vector_create()
{
    return vector_create(unsigned_int_copy_constructor, unsigned_int_destructor,
                         unsigned_int_default_constructor);
}
vector *unsigned_long_vector_create()
{
    return vector_create(unsigned_long_copy_constructor,
                         unsigned_long_destructor,
                         unsigned_long_default_constructor);
}
vector *unsigned_short_vector_create()
{
    return vector_create(unsigned_short_copy_constructor,
                         unsigned_short_destructor,
                         unsigned_short_default_constructor);
}
