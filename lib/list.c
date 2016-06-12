#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "strings.h"
#include "generic.h"
#include "sortable.h"

DEFTYPE(list);
DEFTYPE(dlist);

list cons(printable* car, list cdr) {
    list result = ALLOCATE(sizeof(cell));
    printable* presult = (printable*)result;
    presult->type = list_type();
    define_method(presult->type, to_string, to_string_list);
    define_method(presult->type, insertion_sort, list_insertion_sort);
    define_method(presult->type, length, list_length);
    define_method(presult->type, merge_sort, list_merge_sort);
    define_method(presult->type, reverse, list_reverse);
    define_method(presult->type, append, list_append);
    define_method(presult->type, find, list_find);
    result->car = car;
    result->cdr = cdr;
    return result;
}

printable* list_find(list haystack, printable* needle) {
    list it = haystack;
    while (it != NULL) {
        if (it->car == needle) return it->car;
        it = it->cdr;
    }
    return NULL;
}

list list_reverse(list input) {
    list result = NULL;
    while (input != NULL) {
        result = cons(input->car, result);
        input = input->cdr;
    }
    return result;
}

list make_list(printable** elements, size_t size) {
    size_t i;
    list result = NULL;
    
    for (i = size; i > 0; i--) result = cons(elements[i - 1], result);
    return result;
}

size_t list_length(list input) {
    size_t i = 0;
    list it = input;

    while (it != NULL) {
        i++;
        it = it->cdr;
    }
    return i;
}

list list_append(list a, list b) {
    list result = NULL;
    while (a != NULL) {
        result = cons(a->car, result);
        a = a->cdr;
    }
    while (b != NULL) {
        result = cons(b->car, result);
        b = b->cdr;
    }
    return list_reverse(result);
}

list merge(list odds, list evens, comparison_fn_t cmp) {
    list result = NULL;
    odds = list_merge_sort(odds, cmp);
    evens = list_merge_sort(evens, cmp);
    while (true) {
        if (odds == NULL) return append(reverse(result), evens);
        if (evens == NULL) return append(reverse(result), odds);
        if (cmp(&odds->car, &evens->car) <= 0) {
            result = cons(odds->car, result);
            odds = odds->cdr;
        } else {
            result = cons(evens->car, result);
            evens = evens->cdr;
        }
    }
    return NULL;
}

list list_merge_sort(list in, comparison_fn_t cmp) {
    if (in == NULL) return NULL;
    if (in->cdr == NULL) return in;
    
    list odds = NULL, evens = NULL, it = in;
    size_t i = 0;
    
    while (it != NULL) {
        if ((i & 1) == 1) odds = cons(it->car, odds);
        else evens = cons(it->car, evens);
        it = it->cdr;
        i++;
    }
    return merge(reverse(odds), reverse(evens), cmp);
}

list list_pop(list* in) {
    if (in == NULL) return NULL;
    list result = *in;
    *in = (*in)->cdr;
    return result;
}

void list_push(printable* elt, list* to) {
    *to = cons(elt, *to);
}

list list_insertion_sort(list in, comparison_fn_t cmp) {
    if (in == NULL) return NULL;
    if (in->cdr == NULL) return in;

    list p = in, extra = NULL, copy = NULL, current = NULL, last = NULL;
    
    while (p != NULL) {
        current = list_pop(&p);
        copy = extra;
        last = NULL;
        while (copy != NULL &&
               cmp(&current->car, &copy->car) > 0) {
            last = copy;
            copy = copy->cdr;
        }
        if (last == NULL) {
            extra = cons(current->car, extra);
        } else {
            list tmp = last->cdr;
            last->cdr = current;
            current->cdr = tmp;
        }
    }
    return extra;
}

char* to_string_list(list p) {
    list it = p;
    size_t i = 0, len = list_length(p);
    char** parts = malloc(len * sizeof(char*));
    char* contents, *result;

    while (it != NULL) {
        char* chunk = to_string(it->car);
        parts[i] = chunk;
        it = it->cdr;
        i++;
    }
    contents = join(parts, len, ", ");
	result = ALLOCATE(sizeof(char) * (strlen(contents) + 3));
	sprintf(result, "(%s)", contents);
    free(parts);
    return result;
}

dlist dcons(printable* car, dlist cdr) {
    dlist result = ALLOCATE(sizeof(dcell));
    printable* presult = (printable*)result;
    presult->type = dlist_type();
    define_method(presult->type, to_string, to_string_list);
    define_method(presult->type, insertion_sort, list_insertion_sort);
    define_method(presult->type, length, list_length);
    define_method(presult->type, merge_sort, list_merge_sort);
    define_method(presult->type, reverse, list_reverse);
    define_method(presult->type, append, list_append);
    define_method(presult->type, find, list_find);
    ((list)result)->car = car;
    ((list)result)->cdr = (list)cdr;
    if (cdr != NULL) cdr->dcdr = result;
    return result;
}

dlist dlist_reverse(dlist input) {
    dlist result = NULL;
    while (input != NULL) {
        result = dcons(((list)input)->car, result);
        input = (dlist)((list)input)->cdr;
    }
    return result;
}

dlist dlist_append(dlist a, dlist b) {
    dlist result = NULL;
    while (a != NULL) {
        result = dcons(((list)a)->car, result);
        a = (dlist)((list)a)->cdr;
    }
    while (b != NULL) {
        result = dcons(((list)b)->car, result);
        b = (dlist)((list)b)->cdr;
    }
    return dlist_reverse(result);
}

dlist make_dlist(printable** elements, size_t size) {
    size_t i;
    dlist result = NULL;
    
    for (i = size; i > 0; i--) result = dcons(elements[i - 1], result);
    return result;
}
