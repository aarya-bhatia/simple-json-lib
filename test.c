
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
    /*
    {
        'name': 'aarya',
        'age': 21,
        'student': true,
        'scores': {
            'math': 95.5,
            'cs': 97.9
        }
    }

    root = json {
        json {
            key: name,
            value: aarya
        },
        json {
            key: age,
            value: 21
        },...
    }

    scores = json {
        json {
            key: math,
            value: 96
        },
        json {
            key: cs,
            value 98
        }
    }

    > set(root, "scores", scores)

    root = json {
        json {
            key: name,
            value: aarya
        },
        json {
            key: age,
            value: 21
        },
        ... ,
        json {
            key: scores,
            value: json {
                key: math,
                value: 96
                },
                json {
                    key: cs,
                    value 98
                },
            },
        },
    }
    */
    json_t *root = calloc(1, sizeof *root);
    assert(root);
    assert(!json_get(root, "somekey"));

    json_set(root, "name", "Aarya", VAL_STR);

    assert(json_get(root, "name"));
    assert(json_get(root, "name")->value);
    assert(!strcmp(json_get(root, "name")->value, "Aarya"));

    json_set(root, "name", "Aarya Bhatia", VAL_STR);
    assert(!strcmp(json_get(root, "name")->value, "Aarya Bhatia"));

    int age = 21;
    bool is_student = true;

    json_set(root, "age", &age, VAL_INT);
    assert(json_get(root, "age")->value);
    assert(*(int *)json_get(root, "age")->value == age);

    json_set(root, "student", &is_student, VAL_BOOL);

    float math_score = 95.5, cs_score = 97.9;
    json_t *scores = calloc(1, sizeof *scores);

    json_set(scores, "math", &math_score, VAL_FLOAT);
    json_set(scores, "cs", &cs_score, VAL_FLOAT);

    json_set(root, "scores", scores, VAL_OBJ);

    sstring *s = sstring_default_constructor();
    json_to_string(s, root);

    char *final_s = sstring_to_cstr(s);
    sstring_destructor(s);

    puts(final_s);

    FILE *fptr = fopen("output.json", "w");
    fwrite(final_s, 1, strlen(final_s), fptr);
    fclose(fptr);

    free(final_s);

    json_free(root);
    ///////////

    root = calloc(1, sizeof *root);

    json_t A;
    memset(&A, 0, sizeof A);
    A.key = "A";

    // root = { "A": {} }
    json_set(root, "A", &A, VAL_OBJ);

    json_set(root, "B", "hello", VAL_STR);
    json_set(root, "C", "hello", VAL_STR);

    // json_t *Aptr = json_get(root, "A");
    // assert(Aptr);

    for (json_t *itr = root->child; itr; itr = itr->sibling)
    {
        if (itr->key && !strcmp(itr->key, "A"))
        {
            json_set(itr, "B", "hello", VAL_STR);
            json_set(itr, "C", "hello", VAL_STR);
            break;
        }
    }

    s = sstring_default_constructor();
    json_to_string(s, root);

    final_s = sstring_to_cstr(s);
    puts(final_s);

    sstring_destructor(s);
    free(final_s);
    json_free(root);

    return 0;

    /*
     */
}
