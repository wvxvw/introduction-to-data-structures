#include <stdio.h>

#include "array.h"
#include "int_array.h"

bool is_sparse(const array* sorted) {
    int* first = (int*)sorted->elements[0]->val;
    int* last = (int*)sorted->elements[sorted->length - 1]->val;
    return (int)*last - (int)*first >= sorted->length;
}

int main() {
    printf("Assignment 1.1\n");
    
    array* randoms = make_random_array(27, 13, 67);
    printf("Created random array: %s.\n",
           ((printable*)randoms)->to_string((printable*)randoms));
    printf("Array is sparse: %s.\n", is_sparse(randoms) ? "yes" : "no");

    array* uniques = make_random_unique_array(27, 13);
    printf("Created random unique array: %s.\n",
           ((printable*)uniques)->to_string((printable*)uniques));
    printf("Array is sparse: %s.\n", is_sparse(uniques) ? "yes" : "no");
    
    array* dense = make_dense_sorted_array(27, 13);
    printf("Created dense array: %s.\n",
           ((printable*)dense)->to_string((printable*)dense));
    printf("Array is sparse: %s.\n", is_sparse(dense) ? "yes" : "no");

    array* sparse = make_sparse_sorted_array(27, 13, 7);
    printf("Created sparse array: %s.\n",
           ((printable*)sparse)->to_string((printable*)sparse));
    printf("Array is sparse: %s.\n", is_sparse(sparse) ? "yes" : "no");
    return 1;
}
