/**
 * vector
 * CS 341 - Fall 2022
 */
#include "sstring.h"
#include "vector.h"
#include <string.h>
#include <assert.h>

void print_string(void *elem) {
    assert(elem);
    printf("%s", (char *) elem);
}

int main()
{
    /* PART 1: cstr_to_sstring,
     * sstring_to_cstr,
     * sstring_append
     */
    const char *s1 = "Hello World";

    sstring *ss = cstr_to_sstring(s1);

    test_is_valid_sstring(ss);
    assert(sstring_cmp(ss,s1) == 0);
    assert(sstring_size(ss) == strlen(s1));
    assert(sstring_capacity(ss) > sstring_size(ss));
    sstring_print(ss);

    char *cstr = sstring_to_cstr(ss);

    assert(strlen(cstr)==strlen(s1));
    assert(strcmp(cstr,s1)==0);
    printf("%s\n",cstr);

    sstring_destroy(ss); ss = NULL;
    free(cstr); cstr = NULL;

    sstring *ss1 = cstr_to_sstring("ABCD");
    sstring *ss2 = cstr_to_sstring("EF");

    assert(sstring_size(ss1) == strlen("ABCD"));
    sstring_append(ss1, ss2);

    test_is_valid_sstring(ss1);
    test_is_valid_sstring(ss2);

    sstring_print(ss1);
    sstring_print(ss2);

    assert(sstring_cmp(ss1, "ABCDEF") == 0);
    assert(sstring_size(ss1) == strlen("ABCD") + strlen("EF"));
    assert(sstring_size(ss2) == strlen("EF"));

    sstring_destroy(ss1);
    sstring_destroy(ss2);

    ss1 = NULL; ss2 = NULL;

    /* PART 2*/

    ss = cstr_to_sstring("CS 341");
    ss1 = sstring_default_constructor();
    test_is_valid_sstring(ss1);

    sstring_append(ss1, ss); // ss1 = 'CS 341'

    printf("%s -> %lu \n", sstring_get_buffer(ss1), sstring_size(ss1));
    assert(sstring_size(ss1) == strlen("CS 341"));
    assert(sstring_capacity(ss1) >= 8);
    assert(sstring_cmp(ss1, "CS 341") == 0);

    ss2 = sstring_copy_constructor(ss1);

    assert(sstring_equals(ss, ss1));
    assert(sstring_equals(ss1, ss2));
    assert(sstring_equals(ss2, ss1));

    assert(sstring_size(ss1) ==  sstring_size(ss2));
    assert(sstring_capacity(ss1) >= sstring_capacity(ss2));

    printf("Substituting ss from ");
    sstring_print(ss);
    sstring_substitute(ss, 0, "CS", "MATH"); // ss = MATH 341

    sstring_print(ss);
    assert(sstring_cmp(ss, "MATH 341") == 0); 
    sstring_substitute(ss, strlen("MATH "), "341", "347"); // ss = MATH 347
    sstring_print(ss);

    assert(sstring_cmp(ss, "MATH 347") == 0);
    assert(sstring_size(ss) == strlen("MATH 347"));

    test_is_valid_sstring(ss);
    test_is_valid_sstring(ss1);
    test_is_valid_sstring(ss2);

    vector *v = sstring_split(ss1, ' '); // ["CS","341"]
    assert(vector_size(v) == 2);
    vector_print(v, print_string);
    assert(strcmp((char *)vector_get(v, 0), "CS") == 0);
    assert(strcmp((char *)vector_get(v, 1), "341") == 0);
    vector_destroy(v);
    v = NULL;

    char *c = sstring_slice(ss1, 3, 6);
    assert(c);
    assert(strcmp(c, "341") == 0);
    free(c); c = NULL;

    sstring_destroy(ss);
    sstring_destroy(ss1);
    sstring_destroy(ss2);

    /////////////////////////////////////////////////////////

    sstring *src1 = cstr_to_sstring("This is simple text.");
    sstring *src2 = cstr_to_sstring("");
    sstring *src3 = cstr_to_sstring("a  double  space!  ");
    sstring *src4 = cstr_to_sstring("😋 😋 😋 😋");
    sstring *src5 = cstr_to_sstring("cs 341 cs341");

    char buf[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
        Praesent nec ex vel purus dignissim blandit sit amet non erat. \
        Nulla venenatis leo quis sem porta condimentum.\
        Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae;\
        Duis magna enim, varius ac erat et, blandit auctor risus. Fusce purus felis,\
        mollis posuere vestibulum ac, consequat quis nibh. Aliquam et lectus massa.\
        Vivamus vel odio ac libero luctus imperdiet fringilla eget tellus.\
        Aliquam tempus iaculis augue eu volutpat. Etiam malesuada, quam sed interdum tempus,\
        nibh nisi tempus lorem, quis scelerisque leo sem et ante. Aliquam suscipit velit interdum est ornare,\
        eget pretium nisl varius. Aliquam erat volutpat.";

    sstring *src6 = cstr_to_sstring(buf);
    
    v = sstring_split(src1, ' ');
    vector_print(v, print_string);
    vector_destroy(v);
    v = NULL;
    
    /** vector_destroy(sstring_split(src1, ' ')); */

    vector_destroy(sstring_split(src1, 'i'));
    vector_destroy(sstring_split(src2, '/'));
    vector_destroy(sstring_split(src2, '-'));
    vector_destroy(sstring_split(src3, ' '));
    vector_destroy(sstring_split(src4, ' '));
    vector_destroy(sstring_split(src5, ' '));
    vector_destroy(sstring_split(src5, 's'));
    vector_destroy(sstring_split(src6, '.'));

    sstring_substitute(src5, 4, "341", "241");
    sstring_print(src5);

    sstring_substitute(src5, 0, "341", "241");
    sstring_print(src5);

    sstring_substitute(src5, 0, "241", "");
    sstring_substitute(src5, 0, "241", "");
    sstring_print(src5);

    sstring_substitute(src5, 0, "cs", "Hello World | ");
    sstring_substitute(src5, 0, "cs", "Hello World | ");
    sstring_print(src5);

    sstring_destroy(src1);
    sstring_destroy(src2);
    sstring_destroy(src3);
    sstring_destroy(src4);
    sstring_destroy(src5);
    sstring_destroy(src6);

    c = "%A/%B";
    sstring *sv1 = cstr_to_sstring(c);
    sstring_substitute(sv1,0,"%A","1");
    sstring_substitute(sv1,0,"%B","");
    sstring_print(sv1);
    sstring_destroy(sv1);


    return 0;
}
