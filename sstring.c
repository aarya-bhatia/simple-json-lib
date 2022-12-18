/**
 * vector
 * CS 341 - Fall 2022
 */
#include "sstring.h"
#include "vector.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define GROWTH_FACTOR 2

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/**
 * Align size  will find the closest multiple of 16 for given number.
 * This will ensure buffer size % 16 == 0.
 */
#define BLOCK_SIZE 8
#define ALIGN_SIZE(n) ( (((n)-1) | (BLOCK_SIZE-1)) + 1 )

/** #define DEBUG */

struct sstring {
    char *buffer; /* string buffer */
    size_t size; /* strlen(buffer) */
    size_t capacity; /* buffer size */
};

void *sstring_copy_constructor(void *elem) {
    sstring *original = (sstring *) elem;

    assert(original);
    assert(original->buffer);

    sstring *copy = malloc(sizeof(sstring));
    copy->size = original->size;
    copy->capacity = original->size + 1;
    copy->buffer = calloc(original->size + 1, 1);
    memcpy(copy->buffer, original->buffer, original->size);
    copy->buffer[copy->size] = 0;

    return (void *) copy;
}

void sstring_destructor(void *elem) {
    assert(elem);
    sstring_destroy((sstring *)elem);
}

void *sstring_default_constructor(void) {
    sstring *s = malloc(sizeof(sstring));
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    s->buffer = calloc(INITIAL_CAPACITY, 1);
    return (void *) s;
}

void sstring_putc(sstring *ss, char c)
{
    if(ss->size + 2 >= ss->capacity) {
        ss->buffer = realloc(ss->buffer, ss->capacity * GROWTH_FACTOR);
        ss->capacity *= GROWTH_FACTOR;
        assert(ss->buffer);
    }

    ss->buffer[ss->size++] = c;
    ss->buffer[ss->size] = 0;
}

int sstring_cmp(sstring *s, const char *str)
{
    assert(s); 
    assert(s->buffer);
    assert(str);
    return strcmp(s->buffer, str);
}

int sstring_equals(sstring *s1, sstring *s2)
{
    assert(s1);
    assert(s2);
    assert(s1->buffer);
    assert(s2->buffer);

    if(s1->size != s2->size) {
        return 0;
    }

    if(s1 == s2 || strcmp(s1->buffer, s2->buffer) == 0) {
        return 1;
    }

    return 0;
}

void sstring_print(sstring *ss){
    if(!ss) { puts("NULL"); }

    else { 
#ifdef DEBUG
        printf("%p: sstring(buffer: %s, size: %lu, capacity: %lu)\n",
            ss, ss->buffer, ss->size, ss->capacity); 
#endif
    }
}

char *sstring_get_buffer(sstring *ss){
    return ss ? ss->buffer : NULL;
}

size_t sstring_size(sstring*ss){
    return ss->size;
}

size_t sstring_capacity(sstring*ss){
    return ss->capacity;
}

/**
 * Checks if given sstring is valid
 */
int test_is_valid_sstring(sstring *s){
    assert(s);
    assert(s->buffer);

    /* Size must be less than or equal to capacity */
    assert(s->size+1 <= s->capacity);

    /* The buffer must contain the null byte at last position */
    assert(s->buffer[s->size] == '\0');

    return 1;
}

/**
 * Checks if the given index i is within the bounds of the sstring s.
 */
int test_is_valid_sstring_index(sstring *s, size_t i)
{
    assert(s);
    return i >= 0 && i < s->size;
}

sstring *cstr_to_sstring(const char *input) {
    sstring *s = malloc(sizeof(sstring));
    assert(s);

    size_t inputLength = strlen(input);

    s->buffer = strdup(input);
    s->size = inputLength;
    s->capacity = inputLength + 1;

    assert(s->buffer);

    return s;
}

char *sstring_to_cstr(sstring *input) {
    test_is_valid_sstring(input);
    return strdup(input->buffer);
}

int sstring_append(sstring *this, sstring *addition) {
    test_is_valid_sstring(this);
    test_is_valid_sstring(addition);

    if(addition->size == 0) { return this->size; } 

    if(this->size + addition->size + 1 > this->capacity) {

        this->capacity = ALIGN_SIZE(this->size + addition->size + 1);
        this->buffer = realloc(this->buffer, this->capacity);
        assert(this->buffer);
    }

    for(size_t i = 0; i < addition->size; i++)
    {
        this->buffer[this->size++] = addition->buffer[i];
    }

    this->buffer[this->size] = 0;

    return this->size;
}

vector *sstring_split(sstring *this, char delimiter) {
    test_is_valid_sstring(this);
    assert(delimiter != 0);

#ifdef DEBUG
    printf("%s: %d: split(%s,'%c')\n", __FILE__, __LINE__, this->buffer, delimiter);
#endif

    vector *v = vector_create(string_copy_constructor, string_destructor, string_default_constructor);

    sstring *sbuff = sstring_default_constructor();
    test_is_valid_sstring(sbuff);

    for(size_t i = 0; i < this->size; i++)
    {
        // found word - add to vector
        if(this->buffer[i] == delimiter) {
            vector_push_back(v, sbuff->buffer);

#ifdef DEBUG
            printf("WORD: '%s'\n", sbuff->buffer);
#endif

            sbuff->size = 0;
            sbuff->buffer[0] = 0;
            continue;
        }

        sstring_putc(sbuff, this->buffer[i]);
    }

    // add remainder
    vector_push_back(v, sbuff->buffer);

    // cleanup
    sstring_destructor((void *) sbuff);
    sbuff = NULL;

    return v;
}

/**
 * @param src given string
 * @param target substring to find
 * @param n1 strlen(src)
 * @param n2 strlen(target)
 * @return Given two C strings src and target, find the first index
 * where target is seen in src, or return -1 if none.
 */
ssize_t find_substring_index(char *src, size_t n1, char *target, size_t n2)
{
    assert(src);
    assert(target);

    for(size_t i = 0; i < n1; i++)
    {
        if(i + n2 - 1 >= n1)
        {
            return -1;
        }

        if(strncmp(src + i, target, n2) == 0) 
        {
            return i;
        }
    }

    return -1;
}

int sstring_substitute(sstring *this, size_t offset, char *target,
        char *substitution) {
    test_is_valid_sstring(this);
    assert(offset >= 0);
    assert(offset < this->size);
    assert(target);
    assert(substitution);

#ifdef DEBUG
    printf("substitue(%s) %s to %s\n", this->buffer+offset, target, substitution);
#endif

    size_t targetLen = strlen(target);
    size_t substLen = strlen(substitution);

    ssize_t found = find_substring_index(this->buffer + offset, this->size - offset, target, targetLen);
    
#ifdef DEBUG
    printf("Found %s at position %zu in string %s\n", target, (size_t) found+offset, this->buffer);
#endif

    if(found == -1) { return -1; }

    // The found index was relative to the offset
    // Get absolute position in the string where target is seen
    size_t i = (size_t ) found + offset;

    if(substLen > targetLen && this->size + substLen - targetLen + 1 >= this->capacity)
    {
        this->capacity = ALIGN_SIZE(this->size + substLen - targetLen + 1);
        this->buffer = realloc(this->buffer, this->capacity); 
    }

    assert(this->buffer);
    assert(this->size + substLen - targetLen < this->capacity);

    // src = [A][target][B]
    // substitute(src) = [A][substitute][B]
    
    // Create space for the substitute string
    // Shift B part of the string to the right
    memmove(this->buffer + i + substLen,
            this->buffer + i + targetLen,
            this->size - (i + targetLen));

    // Copy the substitute string after the A part
    memcpy(this->buffer + i, substitution, substLen);

    // String increases in size by the size difference 
    // between target and substitution strings
    this->size += (substLen - targetLen);

    this->buffer[this->size] = 0;

    assert(test_is_valid_sstring(this));

    return 0;
} 

char *sstring_slice(sstring *this, int start, int end) {
    assert(this);
    assert(this->buffer);
    assert((size_t) start >= 0);
    assert((size_t) start < this->size); /* INCLUSIVE */
    assert((size_t) end >= 0);
    assert((size_t) end < this->size + 1); /* EXCLUSIVE */
    assert((size_t) start <= (size_t) end);

    // Extract the part this->buffer[start, ..., end-1]

    char *result = calloc(end-start+1, 1);
    size_t idx = 0;

    for(int i = start; i < end; i++) {
        result[idx++] = this->buffer[i];
    }

    // Null byte is already there from calloc
    
    return result;
}

void sstring_destroy(sstring *this) {
    if(!this) {
        return;
    }

    free(this->buffer);
    memset(this, 0, sizeof(sstring));
    assert(!this->buffer);

    free(this);
}
