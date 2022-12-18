
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

    json_set(root, "name", "Aarya", VAL_STR);

    assert(json_get(root, "name"));
    assert(json_get(root, "name")->value);
    assert(!strcmp(json_get(root, "name")->value, "Aarya"));

    // json_set(root, "name", "Aarya Bhatia", VAL_STR);
    // assert(!strcmp(json_get(root, "name")->value, "Aarya Bhatia"));

    // int age = 21;
    // bool is_student = true;

    // json_set(root, "age", &age, VAL_INT);
    // assert(json_get(root, "root")->value);
    // assert(*(int *)json_get(root, "root")->value == age);

    // json_set(root, "student", &is_student, VAL_BOOL);

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
    free(final_s);

    json_free(root);
    return 0;
}
