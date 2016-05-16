#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "printable.h"
#include "printable_int.h"
#include "printable_float.h"
#include "array.h"
#include "pair.h"
#include "list.h"
#include "strings.h"

char* to_string_array(array p) {
    char** parts = malloc(sizeof(char*) * p->length);
    char* contents, *result;
    size_t i;

    for (i = 0; i < p->length; i++) {
        printable* elt = p->elements[i];
        parts[i] = (char*)to_string(elt);
    }
	contents = join(parts, p->length, ", ");
	result = ALLOCATE(sizeof(char) * (strlen(contents) + 3));
	sprintf(result, "[%s]", contents);
    free(parts);
    return result;
}

array make_empy_array(size_t size) {
    array result = ALLOCATE(sizeof(printable_array));
    result->length = size;
    result->elements = ALLOCATE(size * sizeof(printable*));
    result->printable.to_string = (printer)to_string_array;
    return result;
}

array make_array(size_t size, printable** data) {
    array result = make_empy_array(size);
    size_t i = 0;
    while (i < size) {
        result->elements[i] = data[i];
        i++;
    }
    return result;
}

array sorted(array unsorted, comparison_fn_t cmp) {
    qsort(unsorted->elements, unsorted->length, unsorted->elements[0]->size, cmp);
    return unsorted;
}

array shuffled(array sorted) {
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

array slice(const array input, const size_t from, const size_t to) {
    array result = ALLOCATE(sizeof(printable_array));
    result->length = to - from;
    result->elements = &input->elements[from];
    result->printable.to_string = (printer)input->printable.to_string;
    return result;
}

size_t linsearch(const array input,
                 const void* elt,
                 size_t from,
                 search_direction dir,
                 comparison_fn_t cmp) {
    int i;
    if (dir == FORWARD) {
        for (i = from; i < input->length; i++)
            if (cmp(&input->elements[i], &elt) == 0) break;
    } else {
        for (i = from; i >= 0; i--)
            if (cmp(&input->elements[i], &elt) == 0) break;
    }
    return i;
}

size_t binsearch(const array input, const printable* elt, comparison_fn_t cmp) {
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

array make_random_array(const size_t size,
                         const size_t low,
                         const size_t high,
                         element_generator generator) {
    printable** elts = ALLOCATE(size * sizeof(printable*));
    size_t i = 0;
    time_t t;

    srand((unsigned)time(&t));
    while (i < size) {
        int val = (int)(low + rand() % (high - low));
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}

array make_random_sorted_array(const size_t size,
                                const size_t low,
                                const size_t high,
                                comparison_fn_t cmp,
                                element_generator generator) {
    return sorted(make_random_array(size, low, high, generator), cmp);
}

array make_dense_sorted_array(const size_t size,
                               const size_t from,
                               element_generator generator) {
    printable** elts = ALLOCATE(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = (int)(i + from);
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}
array make_sparse_sorted_array(const size_t size,
                                const size_t from,
                                const size_t deviation,
                                element_generator generator) {
    printable** elts = ALLOCATE(size * sizeof(printable*));
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

array make_random_unique_array(const size_t size,
                                const size_t from,
                                element_generator generator) {
    printable** elts = ALLOCATE(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = (int)(i + from);
        elts[i] = generator(&val);
        i++;
    }
    return shuffled(make_array(size, elts));
}

array make_array_from_pointer(const int* data,
                               const size_t size,
                               element_generator generator) {
    printable** elts = ALLOCATE(size * sizeof(printable*));
    size_t i = 0;
    
    while (i < size) {
        int val = data[i];
        elts[i] = generator(&val);
        i++;
    }
    return make_array(size, elts);
}

array make_increasing_decreasing_array(const size_t half_size,
                                        element_generator generator) {
    printable** elts = ALLOCATE(half_size * 2 * sizeof(printable*));
    size_t i;
    for (i = 0; i < half_size; i++) {
        int odd = half_size * 2 - i;
        int even = (int)(i + 1);
        elts[i * 2] = generator(&odd);
        elts[i * 2 + 1] = generator(&even);
    }
    return make_array(half_size * 2, elts);
}

array make_vedge_array(const size_t half_size,
                        element_generator generator) {
    printable** elts = ALLOCATE(half_size * 2 * sizeof(printable*));
    size_t i;
    for (i = 0; i < half_size; i++) {
        int odd = half_size - i;
        int even = (int)(half_size * 2 - i);
        elts[i] = generator(&odd);
        elts[half_size + i] = generator(&even);
    }
    return make_array(half_size * 2, elts);
}

static long swap_count;

void start_swap_count() { swap_count = 0; }

long get_swap_count() { return swap_count; }

void swap(array input, size_t a, size_t b) {
    printable* temp = input->elements[a];
    input->elements[a] = input->elements[b];
    input->elements[b] = temp;
    swap_count++;
}

void insert(array input, comparison_fn_t cmp, size_t pos) {
    size_t i = pos;
    while (i > 0) {
        printable* candidate = input->elements[i];
        printable* previous = input->elements[i - 1];
        if (cmp(&previous, &candidate) > 0)
            swap(input, i, i - 1);
        else return;
        i--;
    }
}

array insertion_sort(array unsorted, comparison_fn_t cmp) {
    size_t i;
    for (i = 1; i < unsorted->length; i++) {
        printable* previous = unsorted->elements[i - 1];
        printable* candidate = unsorted->elements[i];
        if (cmp(&previous, &candidate) > 0)
            insert(unsorted, cmp, i);
    }
    return unsorted;
}

bool next(iterator_impl* impl) { return impl->it(impl); }

bool next_it(iterator_impl* impl) {
    if (impl->iterated->length > impl->pos) {
        impl->value = impl->iterated->elements[impl->pos];
        impl->pos++;
        return true;
    }
    return false;
}

iterator_impl* iterator(array iterated) {
    iterator_impl *iter = ALLOCATE(sizeof(iterator_impl));
    iter->iterated = iterated;
    iter->pos = 0;
    iter->it = next_it;
    return iter;
}

size_t partition(array partitioned, comparison_fn_t cmp) {
    if (partitioned->length == 0) return 0;
    printable* pivot = partitioned->elements[0];
    size_t i, wall = 1;

    for (i = 2; i < partitioned->length; i++) {
        if (cmp(&partitioned->elements[i], &pivot) < 0) {
            swap(partitioned, i, wall);
            wall++;
        }
    }
    return wall;
}

size_t partition_at(array searched, size_t position, comparison_fn_t cmp) {
    swap(searched, 0, position);
    return partition(searched, cmp);
}

size_t index_of(array searched, printable* elt) {
    size_t i;
    for (i = 0; i < searched->length; i++)
        if (searched->elements[i] == elt) break;
    return i;
}

printable* nth_order_statistic(array searched, size_t order, comparison_fn_t cmp) {
    printable* result = NULL;
    time_t t;
    size_t position, wall;
    size_t part = searched->length * order / 100;

    srand((unsigned)time(&t));
    while (part > 0) {
        position = rand() % searched->length;
        wall = partition_at(searched, position, cmp);
        if (wall == part) break;
        if (wall < part) {
            searched = slice(searched, wall, searched->length);
            part -= wall;
        } else {
            searched = slice(searched, 0, wall);
        }
    }
    /*
     * This may happen when we asked for 100% or more of the array elements,
     * in which case, we will just return the maximum.
     */
    if (searched->length > 0)
        result = (part >= searched->length) ?
                 searched->elements[searched->length - 1]:
                 searched->elements[part];
    return result;
}

pair three_way_partition(array partitioned, comparison_fn_t cmp) {
    time_t t;
    size_t lidx, ridx, i, mid = 1;
    printable* left;
    printable* right;
    pair result = make_pair();
    int default_val = 0;

    if (partitioned->length <= 1) {
        result->first = int_element_generator(&default_val);
        result->last = int_element_generator(&default_val);
        return result;
    }
    srand((unsigned)time(&t));
    lidx = rand() % (partitioned->length / 2);
    ridx = (partitioned->length / 2) + rand() % (partitioned->length / 2);
    left = partitioned->elements[lidx];
    right = partitioned->elements[ridx];
    if (cmp(&left, &right) > 0) {
        swap(partitioned, lidx, ridx);
        left = partitioned->elements[lidx];
        right = partitioned->elements[ridx];
    }
    swap(partitioned, 0, lidx);
    swap(partitioned, partitioned->length - 1, ridx);
    lidx = 1;
    mid = 1;
    ridx = partitioned->length - 1;
    for (i = 0; i < partitioned->length - 2; i++) {
        if (cmp(&partitioned->elements[mid], &left) < 0) {
            swap(partitioned, lidx, mid);
            lidx++;
            mid++;
        } else if ((cmp(&partitioned->elements[mid], &right) < 0)) {
            mid++;
        } else {
            swap(partitioned, ridx - 1, mid);
            ridx--;
        }
    }
    // TODO: Need printable_size
    int lidx_int = (int)lidx;
    int ridx_int = (int)ridx;
    /*
     * This can happen when we don't have anything in the middle.
     * We generate right index s.t. it is useful for indexing the
     * array afterwards, so it can eventually get less then the
     * left index.
     **/
    if (ridx_int < lidx_int) {
        ridx_int = lidx_int;
    }
    result->first = int_element_generator(&lidx_int);
    result->last = int_element_generator(&ridx_int);
    return result;
}

void three_way_quicksort(array unsorted, comparison_fn_t cmp, size_t error) {
    if (unsorted->length <= error) return;
    switch (unsorted->length) {
        case 1: break;
        case 2:
            if (cmp(&unsorted->elements[0], &unsorted->elements[1]) > 0)
                swap(unsorted, 0, 1);
            break;
        default: {
            pair walls = three_way_partition(unsorted, cmp);
            int low = *(int*)walls->first->val;
            int high = *(int*)walls->last->val;
            if (low > 1)
                three_way_quicksort(slice(unsorted, 0, (size_t)low), cmp, error);
            if (low + 1 < high)
                three_way_quicksort(slice(unsorted, (size_t)low, (size_t)high), cmp, error);
            if (high + 1 < unsorted->length)
                three_way_quicksort(slice(unsorted, (size_t)high, unsorted->length), cmp, error);
        }
    }
}

printable* array_max(array in, comparison_fn_t cmp) {
    if (in->length == 0) return NULL;
    size_t i;
    printable* result = in->elements[0];
    for (i = 1; i < in->length; i++)
        if (cmp(&in->elements[i], &result) > 0)
            result = in->elements[i];
    return result;
}

printable* array_min(array in, comparison_fn_t cmp) {
    if (in->length == 0) return NULL;
    size_t i;
    printable* result = in->elements[0];
    for (i = 1; i < in->length; i++)
        if (cmp(&in->elements[i], &result) < 0)
            result = in->elements[i];
    return result;
}

void swap_when_greater(printable** a, printable** b, comparison_fn_t cmp) {
    if (cmp(a, b) > 0) {
        printable* tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

pair array_min_max(array in, comparison_fn_t cmp) {
    if (in->length == 0) return NULL;
    pair result = make_pair();
    if (in->length == 1) {
        result->first = in->elements[0];
        result->last = in->elements[0];
    } else {
        size_t i, len = in->length >> 1 << 1;
        printable* min = in->elements[0];
        printable* max = in->elements[1];
        swap_when_greater(&min, &max, cmp);
        
        for (i = 2; i < len; i += 2) {
            printable* a = in->elements[i];
            printable* b = in->elements[i + 1];
            swap_when_greater(&a, &b, cmp);
            swap_when_greater(&min, &a, cmp);
            swap_when_greater(&b, &max, cmp);
        }
        if (len < in->length) {
            printable* last = in->elements[len];
            swap_when_greater(&last, &max, cmp);
            swap_when_greater(&min, &last, cmp);
        }
        result->first = min;
        result->last = max;
    }
    return result;
}

void bucket_sort(array unsorted, rationalization_fn_t rat, comparison_fn_t cmp) {
    size_t i, key, len = unsorted->length;
    list* buckets = malloc(sizeof(list) * (len + 1));
    pair minmax = array_min_max(unsorted, cmp);
    printable* min = minmax->first;
    printable* max = minmax->last;

    for (i = 0; i < len; i++) buckets[i] = NULL;
    for (i = 0; i < len; i++) {
        key = rat(unsorted->elements[i], min, max, len);
        buckets[key] = cons(unsorted->elements[i], buckets[key]);
    }
    key = 0;
    for (i = 0; i < len; i++) {
        list bucket = buckets[i];
        bucket = merge_sort(bucket, compare_ints);
        while (bucket != NULL) {
            unsorted->elements[key] = bucket->car;
            key++;
            bucket = bucket->cdr;
        }
    }
    free(buckets);
}

array counting_sort(array unsorted, size_t scalar, rationalization_fn_t rat, comparison_fn_t cmp) {
    pair minmax = array_min_max(unsorted, cmp);
    printable* min = minmax->first;
    printable* max = minmax->last;
    size_t* counts = malloc(sizeof(size_t) * (scalar + 1));
    size_t i;
    array copy = make_empy_array(unsorted->length);

    for (i = 0; i < scalar; i++) counts[i] = 0;
    for (i = 0; i < unsorted->length; i++) {
        size_t key = rat(unsorted->elements[i], min, max, scalar);
        counts[key]++;
    }
    for (i = 1; i < scalar + 1; i++) counts[i] += counts[i - 1];
    for (i = unsorted->length; i > 0; i--) {
        size_t j = i - 1;
        size_t key = rat(unsorted->elements[j], min, max, scalar);
        copy->elements[counts[key] - 1] = unsorted->elements[j];
        counts[key]--;
    }
    free(counts);
    return copy;
}
