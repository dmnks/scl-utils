typedef struct {
    char *str;
    char *key;
    char *val;
} kvpair;

typedef kvpair* dict_t;

dict_t *dict_init();
void dict_free(dict_t *dict);
int dict_put(dict_t **dict, char *string);
char *dict_get(dict_t *dict, const char *key);
void dict_dump(dict_t *dict);
