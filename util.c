#include "util.h"

String *wrap_with_quotes(char *str)
{
    String *s = StringDefaultConstructor();
    StringAdd(s, '"');
    StringAddCstr(s, str);
    StringAdd(s, '"');
    return s;
}