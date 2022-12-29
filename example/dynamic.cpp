#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct Json {
    virtual void init() {
        puts("base");
    }
};

struct JsonString: Json {
    void init(){
        puts("string");
    }
};

int main() {
    Json *j = new JsonString();
    j->init();
    delete j;
    return 0;
}