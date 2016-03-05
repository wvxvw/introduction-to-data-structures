#include <stdio.h>

#include "array.h"
#include "int_array.h"

bool is_sparse(const array sorted) {
    return sorted.elements[sorted.length] - sorted.elements[0] > sorted.length;
}

int main() {
    printf("Assignment 1.1\n");
    array* randoms = make_random_array(27);
    printf("Created array: %s\n",
           ((printable*)randoms)->to_string((printable*)randoms));
    return 1;
}
