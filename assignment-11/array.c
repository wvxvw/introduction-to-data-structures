#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array.h"
#include "printable.h"

const char* to_string_array(const array* p) {
    char* parts[p->length * 2];
    int lenghts[p->length * 2];
    char* result;
    size_t i, copied, total = 0;

    for (i = 0; i < p->length; i++) {
        printable* elt = p->elements[i];
        char* chunk = (char*)elt->to_string(elt);
        parts[i * 2] = chunk;
        parts[i * 2 + 1] = ", ";
        lenghts[i * 2] = strlen(chunk);
        lenghts[i * 2 + 1] = 2;
        total += lenghts[i * 2] + 2;
    }
    result = malloc(total * sizeof(char) + 1);
    result[0] = '[';
    copied = 1;
    
    for (i = 0; i < p->length * 2 - 1; i++) {
        strcpy(result + copied, parts[i]);
        copied += lenghts[i];
    }
    result[copied] = ']';
    result[copied + 1] = '\0';
    return result;
}

array* make_array(const size_t size, printable** data) {
    array* result = malloc(sizeof(array));
    size_t i = 0;
    result->length = size;
    result->elements = malloc(size * sizeof(printable));
    result->printable.to_string = (printer)to_string_array;
    
    while (i < size) {
        result->elements[i] = data[i];
        i++;
    }
    return result;
}

void free_array(array* freed) {
    free(freed);
}

array* sorted(array* unsorted, comparison_fn_t cmp) {
    qsort(unsorted->elements, unsorted->length, unsorted->elements[0]->size, cmp);
    return unsorted;
}

array* shuffled(array* sorted) {
    size_t i;
    time_t t;

    srand((unsigned)time(&t));
    
    for (i = 0; i < sorted->length; i++) {
        size_t j = i + rand() / (RAND_MAX / (sorted->length - i) + 1);
        printable* elt = sorted->elements[j];
        sorted->elements[j] = sorted->elements[i];
        sorted->elements[i] = elt;
    }
    return sorted;
}

array* slice(const array* input, const size_t from, const size_t to) {
    printable** elts = input->elements;
    printable** offset = &elts[from];
    return make_array(to - from, offset);
}

size_t linsearch(const array* input,
                 const void* elt,
                 size_t from,
                 search_direction dir,
                 comparison_fn_t cmp) {
    int i;
    if (dir == FORWARD) {
        for (i = from; i < input->length; i++) {
            if (cmp(&input->elements[i], &elt) == 0) {
                break;
            }
        }
    } else {
        printf("linsearch back\n");
        for (i = from; i >= 0; i--) {
            if (cmp(&input->elements[i], &elt) == 0) {
                break;
            }
        }
    }
    return i;
}

size_t binsearch(const array* input, const printable* elt, comparison_fn_t cmp) {
    size_t start = 0;
    size_t end = input->length / 2;

    while (end - start > 1) {
        switch (cmp(&elt, &input->elements[end])) {
            case 0:
                return linsearch(input, elt, end, BACK, cmp);
            case -1:
                end -= (end - start) / 2;
                break;
            case 1:
                start = end;
                end += (input->length - end) / 2;
                break;
        }
    }
    return input->length;
}

array* make_random_array(const size_t size,
                         const size_t low,
                         const size_t high,
                         comparison_fn_t cmp,
                         element_generator generator) {
    printable** elts = malloc(size * sizeof(printable*));
    size_t i = 0;
    time_t t;

    srand((unsigned)time(&t));
    while (i < size) {
        int val = (int)(low + rand() % (high - low));
        elts[i] = generator(&val);
        i++;
    }
    return sorted(make_array(size, elts), cmp);
}

array* make_dense_sorted_array(const size_t size,
                               const size_t from,
                               element_generator generator) {
    printable** elts = malloc(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = (int)(i + from);
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}
array* make_sparse_sorted_array(const size_t size,
                                const size_t from,
                                const size_t deviation,
                                element_generator generator) {
    printable** elts = malloc(size * sizeof(printable*));
    size_t next = from, i = 0;
    time_t t;

    srand((unsigned)time(&t));
    while (i < size) {
        int val = (int)next;
        next += 1 + rand() % (deviation - 1);
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}

array* make_random_unique_array(const size_t size,
                                const size_t from,
                                element_generator generator) {
    printable** elts = malloc(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = (int)(i + from);
        elts[i] = generator(&val);
        i++;
    }
    return shuffled(make_array(size, elts));
}

array* make_array_from_pointer(const int* data,
                               const size_t size,
                               element_generator generator) {
    printable** elts = malloc(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = data[i];
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}
