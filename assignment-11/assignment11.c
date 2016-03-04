#include <stdio.h>

#include "array.h"

bool is_sparse(const array sorted) {
    return sorted.elements[sorted.length] - sorted.elements[0] > sorted.length;
}

int compare_ints(const void* a, const void* b) {
  const int* da = (const int*) a;
  const int* db = (const int*) b;

  return (*da > *db) - (*da < *db);
}

int main() {
    printf("Assignemtn 1.1\n");
    return 1;
}
