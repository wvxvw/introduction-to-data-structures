/**
 * \file queue.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines basic functions for working with printable
 *        FIFO queues.
 *
 * This file contains declarations for basic data-structures needed to
 * work with differently-typed FIFO queues and being able to pretty-print
 * them.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/05/14
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

#include "printable.h"
#include "array.h"

typedef struct queue_val {
    
    printable printable;
    
    array elements;
    
    size_t head;
    size_t tail;
} queue_val;

typedef queue_val* queue;

ASSIGNMENTLIB_API 
printable* queue_push(printable* element, queue q);

ASSIGNMENTLIB_API 
printable* queue_pop(queue q);

ASSIGNMENTLIB_API 
bool queue_can_push(queue q);

ASSIGNMENTLIB_API 
bool queue_can_pop(queue q);

ASSIGNMENTLIB_API 
char* to_string_queue(queue q);

ASSIGNMENTLIB_API
queue make_queue(printable** elements, size_t size);

ASSIGNMENTLIB_API
queue make_empty_queue(size_t size);

#endif // QUEUE_H_
