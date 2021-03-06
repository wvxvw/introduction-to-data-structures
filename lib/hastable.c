#include <string.h>
#include <stdio.h>
#include "printable.h"
#include "generic.h"
#include "pair.h"
#include "list.h"
#include "printable_string.h"
#include "printable_int.h"
#include "hashtable.h"
#include "sortable.h"
#include "strings.h"

DEFTYPE(chashtable);

static size_t default_size = 47;

// Credits: http://www.cse.yorku.ca/~oz/hash.html
unsigned long string_hash(printable* elt) {
    unsigned char* str = to_string(elt);
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

unsigned long int_hash(printable* elt) {
    int val = *(int*)((printable*)elt)->val;
    return val;
}

void upsize(chashtable table) {

}

void populate(chashtable table, list data) {
    size_t i = 0;
    while (data != NULL) {
        if (i >= ((printable*)table)->size) upsize(table);
        pair p = (pair)data->car;
        chashtable_put(table, p->first, p->last);
        data = data->cdr;
    }
}

char* to_string_chashtable(chashtable ct) {
    size_t len = 0, j = 0, i;
    char* result, *contents;
    printable* pct = (printable*)ct;

    for (i = 0; i < pct->size; i++) len += length(ct->keys[i]);
    char** parts = malloc(len * sizeof(char*));

    for (i = 0; i < pct->size; i++) {
        dlist keys = ct->keys[i];
        dlist values = ct->values[i];
        
        while (keys != NULL) {
            char* sval = to_string((printable*)first(values));
            char* skey = to_string((printable*)first(keys));
            char* kv = ALLOCATE(sizeof(char) * (strlen(skey) + strlen(sval) + 3));
            sprintf(kv, "%s: %s", skey, sval);
            parts[j] = kv;
            j++;
            keys = (dlist)((list)keys)->cdr;
            values = (dlist)((list)values)->cdr;
        }
    }
    contents = join(parts, len, ", ");
    char* pattern = "chashtable[%d]{%s}";
    size_t slen = strlen(contents) + strlen(pattern) + 1;
    result = ALLOCATE(sizeof(char) * slen);
    int res = sprintf(result, pattern, pct->size, contents);
    free(parts);
    if (res < 0) printf("Error printing hashtable\n");
    return result;
}

chashtable make_chashtable(hash_fn_t h, size_t size, list data, comparison_fn_t cmp) {
    chashtable result = ALLOCATE(sizeof(printable_chained_hashtable));
    printable* presult = (printable*)result;
    presult->type = chashtable_type();
    presult->size = size;
    define_method(presult->type, to_string, to_string_chashtable);
    define_method(presult->type, put, chashtable_put);
    define_method(presult->type, pop, chashtable_pop);
    define_method(presult->type, length, chashtable_size);
    define_method(presult->type, find, chashtable_find);
    define_method(presult->type, peek, chashtable_get);
    result->keys = ALLOCATE(sizeof(dlist) * size);
    result->values = ALLOCATE(sizeof(dlist) * size);
    presult->val = result->values;
    result->hash = h;
    result->cmp = cmp;
    populate(result, data);
    return result;
}

chashtable make_empty_chashtable(hash_fn_t h, comparison_fn_t cmp) {
    return make_chashtable(h, default_size, NULL, cmp);
}

chashtable make_empty_string_chashtable() {
    return make_chashtable(string_hash, default_size, NULL, compare_strings);
}

chashtable make_string_chashtable(size_t size, list data) {
    return make_chashtable(string_hash, size, data, compare_strings);
}

chashtable make_empty_int_chashtable() {
    return make_chashtable(int_hash, default_size, NULL, compare_ints);
}

chashtable make_int_chashtable(size_t size, list data) {
    return make_chashtable(string_hash, size, data, compare_ints);
}

dlist chashtable_put(chashtable table, printable* key, printable* val) {
    size_t skey = table->hash(key) % chashtable_size(table);
    dlist keys = table->keys[skey];
    dlist values = table->values[skey];
    printable* existing = find(table->keys[skey], key, *table->cmp);

    if (existing == NULL) {
        table->values[skey] = dcons(val, values);
        table->keys[skey] = dcons(key, keys);
        return table->keys[skey];
    } else {
        while (keys != NULL) {
            if (existing == first(keys)) {
                if (val == first(values)) {
                    return keys;
                }
                dlist ins = dcons(val, (dlist)rest(values));
                if (values->dcdr != NULL) {
                    ((list)values->dcdr)->cdr = (list)ins;
                    ins->dcdr = values->dcdr;
                } else {
                    table->values[skey] = ins;
                }
                return ins;
            }
            keys = (dlist)rest(keys);
            values = (dlist)rest(values);
        }
    }
    return NULL;
}

printable* chashtable_pop(chashtable table, printable* key) {
    size_t skey = table->hash(key) % chashtable_size(table);
    dlist keys = table->keys[skey];
    dlist values = table->values[skey];

    while (keys != NULL) {
        printable* check = first(keys);
        if (check == NULL) continue;
        if ((*table->cmp)(&check, &key) == 0) {
            dlist lkey = keys->dcdr;
            dlist lval = values->dcdr;
            if (lkey != NULL) {
                ((list)lkey)->cdr = (list)rest(keys);
                ((list)lval)->cdr = (list)rest(values);
            } else {
                table->keys[skey] = (dlist)rest(keys);
                table->values[skey] = (dlist)rest(values);
            }
            keys->dcdr = lkey;
            values->dcdr = lval;
            return first(values);
        }
        keys = (dlist)rest(keys);
        values = (dlist)rest(values);
    }
    return NULL;
}

printable* chashtable_get(chashtable table, printable* key) {
    size_t skey = table->hash(key) % ((printable*)table)->size;
    dlist keys = table->keys[skey];
    dlist values = table->values[skey];

    while (keys != NULL) {
        printable* check = first(keys);
        if ((*table->cmp)(&check, &key) == 0)
            return first(values);
        keys = (dlist)rest(keys);
        values = (dlist)rest(values);
    }
    return NULL;
}

printable* chashtable_find(chashtable table, printable* val, comparison_fn_t cmp) {
    size_t i, len = chashtable_size(table);
    
    for (i = 0; i < len; i++) {
        dlist keys = table->keys[i];
        dlist values = table->values[i];
        
        while (keys != NULL) {
            printable* check = first(values);
            if (cmp(&check, &val) == 0)
                return first(values);
            keys = (dlist)rest(keys);
            values = (dlist)rest(values);
        }
    }
    return NULL;
}

size_t chashtable_size(chashtable table) {
    return ((printable*)table)->size;
}
