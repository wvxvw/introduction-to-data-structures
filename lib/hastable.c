#include <string.h>
#include <stdio.h>
#include "printable.h"
#include "generic.h"
#include "pair.h"
#include "list.h"
#include "printable_string.h"
#include "hashtable.h"
#include "sortable.h"
#include "strings.h"

DEFTYPE(chashtable);

static size_t default_size = 47;

// Credits: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void upsize(chashtable table) {

}

void populate(chashtable table, list data) {
    size_t i = 0;
    while (data != NULL) {
        if (i >= table->length) upsize(table);
        pair p = (pair)data->car;
        unsigned char* key = (unsigned char*)p->first->val;
        printable* val = p->last;
        chashtable_put(table, key, val);
    }
}

char* to_string_chashtable(chashtable ct) {
    size_t len = 0, j = 0, i;
    char* result, *contents;

    for (i = 0; i < ct->length; i++) len += length(ct->keys[i]);
    char** parts = malloc(len * sizeof(char*));

    for (i = 0; i < ct->length; i++) {
        dlist keys = ct->keys[i];
        dlist values = ct->values[i];
        while (keys != NULL) {
            char* skey = to_string(((list)keys)->car);
            char* sval = to_string(((list)values)->car);
            char* kv = ALLOCATE(sizeof(char) * (strlen(skey) + strlen(sval) + 3));
            sprintf(kv, "%s: %s", skey, sval);
            parts[j] = kv;
            j++;
        }
    }
    contents = join(parts, len, ", ");
    result = ALLOCATE(sizeof(char) * (strlen(contents) + 15));
    sprintf(result, "chashtable[%d]{%s}", ct->length, contents);
    free(parts);
    return result;
}

chashtable make_chashtable(hash_fn_t h, size_t size, list data) {
    chashtable result = ALLOCATE(sizeof(printable_chained_hashtable));
    printable* presult = (printable*)result;
    presult->type = chashtable_type();
    define_method(presult->type, to_string, to_string_chashtable);
    result->length = size;
    result->keys = ALLOCATE(sizeof(size_t) * result->length);
    result->values = ALLOCATE(sizeof(dlist) * result->length);
    result->hash = h;
}

chashtable make_empty_chashtable(hash_fn_t h) {
    return make_chashtable(h, default_size, NULL);
}

dlist chashtable_put(chashtable table, unsigned char* key, printable* val) {
    size_t skey = table->hash(key) % table->length;
    if (find(table->values[skey], val) == NULL) {
        table->values[skey] = dcons(val, table->values[skey]);
        table->keys[skey] =
                dcons((printable*)make_printable_string(key), table->keys[skey]);
        return table->keys[skey];
    }
    return NULL;
}

printable* chashtable_pop(chashtable table, unsigned char* key) {
    size_t skey = table->hash(key) % table->length;
    dlist keys = table->keys[skey];
    dlist values = table->values[skey];
    printable_string* ps = make_printable_string(key);

    while (keys != NULL) {
        if (compare_strings(&((list)keys)->car->val, &ps) == 0) {
            dlist lkey = keys->dcdr;
            dlist lval = values->dcdr;
            ((list)lkey)->cdr = ((list)keys)->cdr;
            ((list)lval)->cdr = ((list)values)->cdr;
            keys->dcdr = lkey;
            values->dcdr = lval;
            return ((list)values)->car;
        }
        keys = (dlist)((list)keys)->cdr;
        values = (dlist)((list)values)->cdr;
    }
    return NULL;
}

printable* chashtable_get(chashtable table, unsigned char* key) {
    size_t skey = table->hash(key) % table->length;
    printable_string* ps = make_printable_string(key);
    dlist keys = table->keys[skey];
    dlist values = table->values[skey];

    while (keys != NULL) {
        if (compare_strings(&((list)keys)->car->val, &ps) == 0) {
            return ((list)values)->car;
        }
        keys = (dlist)((list)keys)->cdr;
        values = (dlist)((list)values)->cdr;
    }
}
