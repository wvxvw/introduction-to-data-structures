#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "generic.h"
#include "sortable.h"

static vt** types = NULL;
static size_t types_len = 0;
static size_t types_cap = 0;

vt* type_of(printable* p) {
    return types[p->type];
}

size_t make_type(char* type) {
    size_t result = types_len;
    register_type(types_len, type);
    return result;
}

char* to_string_type(vt* type) {
    char* result = ALLOCATE(sizeof(char) * 50);
	sprintf(result, "[%s](len: %d, cap: %d)", type->name, type->len, type->cap);
    return result;
}

void register_type(size_t type, char* name) {
    size_t i;
    if (types == NULL) {
        types_cap = 8;
        types_len = 0;
        types = malloc(types_cap * sizeof(vt*));
        for (i = 0; i < types_cap; i++) types[i] = NULL;
    } else if (types_cap == types_len) {
        types_cap *= 2;
        vt** tmp = malloc(types_cap * sizeof(vt*));
        // Trying to make Valgrind happy
        for (i = 0; i < types_len; i++) tmp[i] = types[i];
        free(types);
        types = tmp;
    }
    vt* result = malloc(sizeof(vt));
    result->name = name;
    result->cap = 0;
    result->len = 0;
    result->methods = NULL;
    result->generics = NULL;
    types[types_len] = result;
    types_len++;
}

void define_method(size_t type, void* generic, void* method) {
    if (types == NULL) {
        printf("You must register type first.");
        return;
    }
    vt* table = types[type];
    size_t i;
    
    if (table->methods == NULL) {
        table->cap = 8;
        table->len = 0;
        table->methods = malloc(table->cap * sizeof(char*));
        table->generics = malloc(table->cap * sizeof(char*));
    } else if (table->cap == table->len) {
        table->cap *= 2;
        void* tmp = malloc(table->cap * sizeof(char*));
        void* gtmp = malloc(table->cap * sizeof(char*));
        memcpy(tmp, table->methods, table->len);
        memcpy(gtmp, table->generics, table->len);
        free(table->methods);
        free(table->generics);
        table->methods = tmp;
        table->generics = gtmp;
    }
    for (i = 0; i < table->len; i++) {
        if (table->generics[i] == generic &&
            table->methods[i] == method) return;
    }
    table->methods[table->len] = method;
    table->generics[table->len] = generic;
    table->len++;
}

void* find_method(size_t type, void* generic) {
    vt* table = types[type];
    if (table == NULL || table->methods == NULL) return NULL;
    size_t i;
    for (i = 0; i < table->len; i++) {
        if (table->generics[i] == generic)
            return table->methods[i];
    }
    return NULL;
}

void debug_vt(size_t type, void* generic) {
    if (types == NULL) {
        printf("No types were initialized. type: %d, generic: %p\n", type, generic);
    }
    vt* table = types[type];
    size_t i;
    if (table == NULL) {
        printf("Cannot find virtual table. type: %d, generic: %p\n", type, generic);
        return;
    }
    if (table->methods == NULL) {
        printf("Cannot find methods table. type: %d, generic: %p, type: %s\n",
               type, generic, to_string_type(table));
        return;
    }
    if (table->generics == NULL) {
        printf("Cannot find generics table. type: %d, generic: %p, type: %s\n",
               type, generic, to_string_type(table));
        return;
    }
    printf("Method not defined. type: %d, generic: %p, type: %s\n",
           type, generic, to_string_type(table));
    for (i = 0; i < table->len; i++) {
        printf("  generic: %p, method: %p\n", table->generics[i], table->methods[i]);
    }
}
