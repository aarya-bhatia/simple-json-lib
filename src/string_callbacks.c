#include "common.h"
#include "Aarya/String.h"

char *null_to_string(void *elem)
{
    (void)elem;
    return strdup("null");
}

char *string_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }
    String *s = wrap_with_quotes(strdup(elem));
    char *str = StringToCstr(s);
    StringDestructor(s);
    return str;
}

char *double_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    char *s;
    asprintf(&s, "%f", *(double *)elem);
    return s;
}

char *float_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    char *s;
    asprintf(&s, "%f", *(float *)elem);
    return s;
}

char *int_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    char *s;
    asprintf(&s, "%d", *(int *)elem);
    return s;
}

char *boolean_to_string(void *elem)
{
    if (!elem)
    {
        return NULL;
    }

    return *(char *)elem == 0 ? strdup("false") : strdup("true");
}
