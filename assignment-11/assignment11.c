#include <stdio.h>
#include <float.h>

#include "printable.h"
#include "array.h"
#include "pair.h"
#include "int_array.h"
#include "float_array.h"

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

/** \brief Given \c z find such \c a[i] and \c b[i] that
 *        \c z = \c a[i] + \c b[i].
 *
 *  \param a Array of floats (potential summands).
 *  \param b Array of floats (potential summands).
 *  \param z The sum whose summands we search for.
 *  \param cmp The comparision function suitable for \c qsort.
 *  \return The \c pair whose \c first and \c last elements
 *          are the summands of \c z.
 */
pair* summands_of(const array* a, const array* b, const float z, comparison_fn_t cmp) {
    pair* result = make_pair();
    array* shortest;
    array* longest;
    size_t i;

    if (a->length < b->length) {
        shortest = sorted((array*)a, cmp);
        longest = (array*)b;
    } else {
        shortest = sorted((array*)b, cmp);
        longest = (array*)a;
    }
    for (i = 0; i < longest->length; i++) {
        float* val = longest->elements[i]->val;
        printable_float* diff = make_printable_float(z - *val);
        size_t pos = binsearch(shortest, (printable*)diff, cmp);
        if (pos >= shortest->length) continue;
        float* other = shortest->elements[pos]->val;
        result->first = (printable*)make_printable_float((float)*val);
        result->last = (printable*)make_printable_float((float)*other);
        break;
    }
    return result;
}

void report(array* tested, char* message) {
    printf(message, to_string((printable*)tested));
    if (!is_sparse(tested)) {
        printf("Array is dense.\n");
    } else {
        printf("Array is sparse.\n");
        size_t missing = binsearch_missing(tested);
        printf("The first gap is at: %d\n", (int)missing);
    }
}

void test_question_3() {
    int ints[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    array* test = make_array_from_pointer(
        ints, 8, float_element_generator);

    printf("Floats: %s\n", to_string((printable*)test));
    pair* summands = summands_of(test, test, 15, compare_floats);
    printf("15 = %s + %s\n",
           to_string(summands->first),
           to_string(summands->last));
}

void test_iterator() {
    int ints[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    array* test = make_array_from_pointer(
        ints, 8, float_element_generator);
    iterator_impl* it = iterator(test);
    printf("Going to iterate\n");
    while (next(it)) {
        printf("Value: %s\n", to_string(it->value));
    }
    printf("Finished to iterate\n");
}

int main() {
    printf("Assignment 1.1\n");
    
    report(make_random_sorted_array(27, 13, 67, compare_ints, int_element_generator),
           "Created random array: %s.\n");
    
    report(make_random_unique_array(27, 13, int_element_generator),
           "Created random unique array: %s.\n");

    report(make_dense_sorted_array(27, 13, int_element_generator),
           "Created dense array: %s.\n");

    report(make_sparse_sorted_array(27, 13, 7, int_element_generator),
           "Created sparse array: %s.\n");

    int ints[11] = {1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13};
    array* test = make_array_from_pointer(ints, 11, int_element_generator);
    report(test, "Created special array: %s.\n");

    int ints1[11] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    array* test1 = make_array_from_pointer(ints1, 11, int_element_generator);
    report(test1, "Created another special array: %s.\n");

    int ints2[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13};
    array* test2 = make_array_from_pointer(ints2, 12, int_element_generator);
    report(test2, "Created last special array: %s.\n");

    test_question_3();
    
    array* test3 = make_array_from_pointer(ints2, 12, float_element_generator);

    printf("Floats: %s\n", to_string((printable*)test3));
    pair* summands = summands_of(test3, test3, 21, compare_floats);
    printf("21 = %f + %f\n", *(float*)summands->first->val, *(float*)summands->last->val);

    array* isorted = make_random_array(27, 13, 67, int_element_generator);
    printf("Before sorted: %s\n", to_string((printable*)isorted));
    isorted = insertion_sort(isorted, compare_ints);
    printf("Insetion sorted: %s\n", to_string((printable*)isorted));

    size_t i;
    for (i = 1; i < 6; i++) {
        array* decinc = make_increasing_decreasing_array(i, int_element_generator);
        printf("Prepare Q1 sequence: %s\n", to_string((printable*)decinc));
        start_swap_count();
        decinc = insertion_sort(decinc, compare_ints);
        printf("Sorted Q1 sequence: %s, swaps performed: %d\n",
               to_string((printable*)decinc),
               (int)get_swap_count());
    }
    for (i = 1; i < 10; i++) {
        array* decinc = make_vedge_array(i, int_element_generator);
        printf("Prepare Q2 sequence: %s\n", to_string((printable*)decinc));
        start_swap_count();
        decinc = insertion_sort(decinc, compare_ints);
        printf("Sorted Q2 sequence: %s, swaps performed: %d\n",
               to_string((printable*)decinc),
               (int)get_swap_count());
    }
    test_iterator();
    return 1;
}
