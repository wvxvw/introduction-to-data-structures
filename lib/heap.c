#include <string.h>
#include <stdio.h>
#include <math.h>

#include "generic.h"
#include "heap.h"
#include "strings.h"
#include "printable_int.h"

DEFTYPE(lheap);

DEFTYPE(aheap);

lcell make_lheap_cell(printable* val) {
    lcell result = ALLOCATE(sizeof(lheap_cell));
    result->val = val;
    result->left = NULL;
    result->right = NULL;
    return result;
}

lheap lheapify(printable** raw, size_t size, comparison_fn_t cmp) {
    lcell head = make_lheap_cell(raw[0]);
    lheap result = ALLOCATE(sizeof(lheap));
    size_t i;
    printable* presult = (printable*)result;

    presult->type = lheap_type();
    define_method(presult->type, to_string, to_string_lheap);
    result->cmp = cmp;
    result->head = head;
    for (i = 1; i < size; i++) lput(result, raw[i]);
    return result;
}

printable* lpeak(lheap heap) {
    return heap->head->val;
}

printable* lpop(lheap heap) {
    /* TODO: */
    return heap->head->val;
}

lcell lbubble(lcell cell, comparison_fn_t cmp) {
    if (cell == NULL || cell->left == NULL) return cell;
    if (cmp(&cell->val, &cell->left->val) > 0) {
        lcell tmp = cell->left;
        cell->left = tmp->left;
        tmp->left = cell;
        lbubble(cell, cmp);
        return tmp;
    }
    cell->right = cell->left->right;
    cell->left->right = NULL;
    lbubble(cell->left, cmp);
    return cell;
}

printable* lput(lheap heap, printable* val) {
    lcell new_head = make_lheap_cell(val);
    new_head->left = heap->head;
    if (heap->head != NULL) {
        new_head->right = heap->head->right;
        heap->head->right = NULL;
    }
    heap->head = new_head;
    heap->head = lbubble(heap->head, heap->cmp);
    return val;
}

char* to_string_lheap_cell(lcell cell) {
    char* left;
    char* right;
    char* val;
    char* nil;
    
    nil = ALLOCATE(4 * sizeof(char));
    strcpy(nil, "nil");
    left = (cell->left != NULL) ? to_string_lheap_cell(cell->left) : nil;
    right = (cell->right != NULL) ? to_string_lheap_cell(cell->right) : nil;
    val = (cell->val != NULL) ? to_string(cell->val) : nil;
    char* result = ALLOCATE((strlen(left) + strlen(right) + strlen(val) + 4) * sizeof(char));
    sprintf(result, "(%s, %s, %s)", left, val, right);
    return result;
}

char* to_string_lheap(lheap heap) {
    char* content = to_string_lheap_cell(heap->head);
    char* result = ALLOCATE((strlen(content) + strlen("lheap()")) * sizeof(char));
    sprintf(result, "lheap(%s)", content);
    return result;
}

/* TODO: Move this into array */
void hswap(printable** elements, size_t a, size_t b) {
    printable* tmp = elements[a];
    elements[a] = elements[b];
    elements[b] = tmp;
}

void abubble_up(aheap heap, size_t child) {
    size_t left = (child << 1) - 1;
    size_t right = child << 1;
    size_t parent = child;

    printf("abubble_up left: %d, right: %d, child: %d\n", (int)left, (int)right, (int)child);
    if (left < heap->size &&
        heap->cmp(&heap->elements[left], &heap->elements[parent]) > 0)
        parent = left;
    if (right < heap->size &&
        heap->cmp(&heap->elements[right], &heap->elements[parent]) > 0)
        parent = right;
    if (parent != child) {
        hswap(heap->elements, child, parent);
        abubble_up(heap, parent);
    }
}

void abubble_down(aheap heap, size_t child) {

}

void resize(aheap heap, size_t new_size) {
    printable** old = heap->elements;
    size_t i;
    
    heap->allocated = heap->allocated << 1;
    heap->elements = ALLOCATE(sizeof(printable*) * heap->allocated);
    for (i = 0; i < heap->size; i++) heap->elements[i] = old[i];
}

aheap make_aheap(size_t size, comparison_fn_t cmp) {
    aheap result = ALLOCATE(sizeof(array_heap));
    printable* presult = (printable*)result;

    result->allocated = pow(2.0, 1.0 + (double)(size_t)log2((double)size));
    result->elements = ALLOCATE(sizeof(printable*) * result->allocated);
    result->size = 0;
    result->cmp = cmp;
    presult->type = aheap_type();
    define_method(presult->type, to_string, to_string_aheap);
    return result;
}

aheap make_empty_aheap(comparison_fn_t cmp) {
    aheap result = make_aheap(DEFAULT_HEAP_SIZE, cmp);
    return result;
}

aheap aheapify(printable** raw, size_t size, comparison_fn_t cmp) {
    aheap result = make_aheap(size, cmp);
    size_t i;

    result->size = size;
    for (i = 0; i < size; i++) result->elements[i] = raw[i];
    for (i = (result->size >> 1) + 1; i > 0; i--) abubble_up(result, i);
    return result;
}

printable* apeak(aheap heap) {
    if (heap->size == 0) return NULL;
    return heap->elements[0];
}

printable* apop(aheap heap) {
    if (heap->size == 0) return NULL;
    printable* result = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    abubble_down(heap, 0);
    return result;
}

printable* aput(aheap heap, printable* val) {
    if (heap->size == heap->allocated) resize(heap, heap->size * 2);
    heap->elements[heap->size] = val;
    heap->size++;
    abubble_up(heap, heap->size);
    return val;
}

char* to_string_aheap(aheap heap) {
    printable_int* cap = make_printable_int(heap->allocated);
    char* scap = to_string((printable*)cap);
    char* pattern = "heap[%s/%s]{%s}";
    char* contents;

    if (heap->size > 0) {
        size_t i = heap->allocated;
        size_t tier = 0;
        char** levels = malloc((size_t)log2((double)i) + 1);

        while (i > 1) {
            size_t j = i >> 1;
            size_t k = j;
            char** level = malloc(j);

            while (k < i) {
                if (k < heap->size) {
                    char* chunk = to_string(heap->elements[k]);
                    level[k - j] = chunk;
                } else {
                    level[k - j] = " ";
                }
                k++;
            }
            levels[tier] = join(level, j, " ");
            tier++;
            i = j;
            free(level);
        }
        contents = join(levels, tier, "\n");
        free(levels);
    } else {
        contents = "";
    }
    printable_int* size = make_printable_int(heap->size);
    char* ssize = to_string((printable*)size);
    size_t len = strlen(contents) + strlen(pattern) +
                 strlen(scap) + strlen(ssize) + 1;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, ssize, scap, contents);
    if (ret < 0) printf("Error printing aheap\n");
    return result;
}
