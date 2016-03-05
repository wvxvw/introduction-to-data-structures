#include <stdio.h>

#include "array.h"
#include "int_array.h"

/** \brief Find out whether the give \c array is sparce, i.e.
 *         whether it has all of its elements in increasing order
 *         without ``gaps''.
 *
 *  \param sorted The array to check
 *  \return true iff there are ``gaps'' in the array.
 */
bool is_sparse(const array* sorted) {
    int* first = (int*)sorted->elements[0]->val;
    int* last = (int*)sorted->elements[sorted->length - 1]->val;
    
    return (int)*last - (int)*first >= sorted->length;
}

/** \brief Find the index of the first element after the ``gap''.
 *
 *  \param sparse The array to look in
 *  \return the index of the element right after the first gap.
 *
 *  This task is equivalent to finding the shortest dense prefix of
 *  the given array, where by ``dense'' I mean that all elements in
 *  this array are in increasing order and there is no three elements
 *  N1, N2 and N3 s.t. N1 > N2 > N3 and N2 is not a member of the
 *  given array, but N1 and N3 are.
 */
size_t binsearch_missing(const array* sparse) {
    size_t start = 0, end = sparse->length / 2;
    array* cut = slice(sparse, start, end);
    
    while (end - start > 1) {
        if (is_sparse(cut)) {
            end -= (end - start) / 2;
        } else {
            start = end - 1;
            end += (sparse->length - end) / 2;
        }
        free_array(cut);
        cut = slice(sparse, start, end);
    }
    return end + 1;
}

void report(array* tested, char* message) {
    printf(message, ((printable*)tested)->to_string((printable*)tested));
    if (!is_sparse(tested)) {
        printf("Array is dense.\n");
    } else {
        printf("Array is sparse.\n");
        size_t missing = binsearch_missing(tested);
        printf("The first gap is at: %d\n", (int)missing);
    }
}

int main() {
    printf("Assignment 1.1\n");
    
    report(make_random_array(27, 13, 67),
           "Created random array: %s.\n");
    
    report(make_random_unique_array(27, 13),
           "Created random unique array: %s.\n");

    report(make_dense_sorted_array(27, 13),
           "Created dense array: %s.\n");

    report(make_sparse_sorted_array(27, 13, 7),
           "Created sparse array: %s.\n");

    int ints[11] = {1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13};
    report(make_array_from_pointer(ints, 11),
           "Created special array: %s.\n");

    int ints1[11] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    report(make_array_from_pointer(ints1, 11),
           "Created another special array: %s.\n");

    int ints2[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13};
    report(make_array_from_pointer(ints2, 12),
           "Created last special array: %s.\n");
    return 1;
}
