#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dict.h"
#include "../src/sclmalloc.h"
#include "../src/lib_common.h"

dict_t *dict_init()
{
    return calloc(1, sizeof(kvpair*));
}

void dict_free(dict_t *dict)
{
    int i = 0;
    kvpair *p;
    while ((p = dict[i++])) {
        free(p->str);
        free(p);
    }
    free(dict);
}

int dict_put(dict_t **dict, char *string)
{
    int i = 0;
    int size = 0;
    char **parts;
    char *key;
    char *val;
    bool update = false;
    kvpair *p;

    parts = split(string, '=');
    key = parts[0];
    val = parts[1];
    free(parts);

    while ((p = (*dict)[i++])) {
        if (strcmp(p->key, key))
            continue;
        update = true;
        break;
    }

    if (!update) {
        size = i + 1;
        *dict = realloc(*dict, size * sizeof(kvpair*));
        p = malloc(sizeof(kvpair));
        (*dict)[size - 1] = NULL;
        (*dict)[size - 2] = p;
    }

    p->str = string;
    p->key = key;
    p->val = val;

    return 0;
}

char *dict_get(dict_t *dict, const char *key)
{
    int i = 0;
    kvpair *p;
    while ((p = dict[i++]))
        if (strcmp(p->key, key) == 0)
            return p->val;
    return NULL;
}

void dict_dump(dict_t *dict)
{
    int i = 0;
    kvpair *p;
    while ((p = dict[i++]))
        printf("%s=%s\n", p->key, p->val);
}
