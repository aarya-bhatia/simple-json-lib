#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define CAT(A,B) A ## B
#define CATX(A,B) CAT(A,B)

#define STR(A) #A
#define STRX(A) STR(A)

#define HELLO 1

typedef struct st {
    int a;
    int b;
} st;

#define make_func(var) func_ ## var

void make_func(a)(st s) {
    printf("%d ", s.a);
}

void make_func(b)(st s) {
    printf("%d ", s.b);
}

int main()
{
    int x0 = 3;

    printf("%s\n", STRX(CATX(HELLO,1)));

    printf("%s = %d\n", STRX(CATX(x,0)), CATX(x,0));

    st s1 = { 1, 2 };
    func_a(s1);
    func_b(s1);

    return 0;
}
