/**
 * \file geometry/point.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines point data-structure
 *
 * This file contains declarations useful for dealing with points on a
 * plain.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef GEOMETRY_POINT_H_
#define GEOMETRY_POINT_H_

#include <float.h>
#include "printable.h"

typedef struct point {
    printable printable;
} point;

float tangent(point* p);

float atanxy(point* p);

char* point_to_string(point* p);

printable* random_point_element_generator(void* elt);

printable* printable_tangent(printable* p);

printable* printable_atanxy(printable* p);

int compare_points(const void* a, const void* b);

size_t rationalize_point(printable* elt, printable* min, printable* max, size_t range);

#endif // GEOMETRY_POINT_H_
