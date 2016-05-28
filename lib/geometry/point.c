#include <float.h>
#include <stdio.h>
#include <math.h>

#include "generic.h"
#include "geometry/point.h"
#include "printable.h"
#include "printable_float.h"
#include "pair.h"

DEFTYPE(point);

float tangent(point* p) {
    pair coords = (pair)((printable*)p)->val;
    float x = *(float*)coords->first->val;
    float y = *(float*)coords->last->val;
    if (x == 0.0) return 1;
    return y / x;
}

float atanxy(point* p) {
    pair coords = (pair)((printable*)p)->val;
    float x = *(float*)coords->first->val;
    float y = *(float*)coords->last->val;
    if (x == 0.0) return 1;
    if (y == 0.0) return 0;
    return atan2(x, y);
}

char* point_to_string(point* p) {
    size_t size = ((printable*)p)->size;
    char* result = ALLOCATE(sizeof(char) * size);
    pair coords = (pair)((printable*)p)->val;

    snprintf(result, size, "{x: %.4f, y: %.4f, t: %.4f}",
             *(float*)coords->first->val,
             *(float*)coords->last->val,
             atanxy(p));
    return result;
}

printable* random_point_element_generator(void* elt) {
    point* result = ALLOCATE(sizeof(point));
    printable* presult = (printable*)result;
    pair coords = make_pair();
    float x, y;
    
    x = (float)rand() / (float)RAND_MAX;
    y = (float)rand() / (float)RAND_MAX;
    coords->first = (printable*)make_printable_float(x);
    coords->last = (printable*)make_printable_float(y);
    presult->val = ALLOCATE(sizeof(pair));
    presult->val = coords;
    presult->type = point_type();
    define_method(presult->type, to_string, point_to_string);
    presult->size = (3 + FLT_DIG) * 3 + 16;
    return presult;
}

printable* printable_tangent(printable* p) {
    point* pt = (point*)p;
    return (printable*)make_printable_float(tangent(pt));
}

printable* printable_atanxy(printable* p) {
    point* pt = (point*)p;
    return (printable*)make_printable_float(atanxy(pt));
}

int compare_points(const void* a, const void* b) {
    point* pa = *(point**)a;
    point* pb = *(point**)b;
    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    float fpa = atanxy(pa);
    float fpb = atanxy(pb);
    return (fpa > fpb) - (fpa < fpb);
}

size_t rationalize_point(printable* elt, printable* min, printable* max, size_t range) {
    float n = atanxy((point*)min);
    float x = atanxy((point*)max);
    float e = atanxy((point*)elt);
    if (x == n) return 0;
    return (size_t)(range * ((e - n) / (x - n)));
}
