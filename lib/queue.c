#include <string.h>
#include <stdio.h>
#include "queue.h"
#include "strings.h"

printable* queue_push(printable* element, queue q) {
    printable* result = NULL;
    if (queue_can_push(q)) {
        result = element;
        q->elements->elements[q->tail] = element;
        q->tail = (q->tail + 1) % q->elements->length;
    }
    return result;
}

printable* queue_pop(queue q) {
    printable* result = NULL;
    if (queue_can_pop(q)) {
        result = q->elements->elements[q->head];
        q->head = (q->head + 1) % q->elements->length;
    }
    return result;
}

size_t queue_length(queue q) {
    if (q->head < q->tail) return q->tail - q->head;
    if (q->head == q->tail) return 0;
    return q->tail + q->elements->length - q->head;
}

bool queue_can_push(queue q) {
    return (q->tail + 1) % q->elements->length != q->head;
}

bool queue_can_pop(queue q) { return q->tail != q->head; }

char* to_string_queue(queue q) {
    size_t len = queue_length(q);
    size_t size = q->elements->length;
    char** parts = malloc(sizeof(char*) * len);
    char* contents, *result;
    size_t i;

    for (i = 0; i < len; i++) {
        printable* elt = q->elements->elements[(i + q->head) % size];
        parts[i] = (char*)to_string(elt);
    }
	contents = join(parts, len, ", ");
	result = ALLOCATE(sizeof(char) * (strlen(contents) + 8));
	sprintf(result, "queue[%s]", contents);
    free(parts);
    return result;
}

queue make_queue(printable** elements, size_t size) {
    queue result = ALLOCATE(sizeof(queue_val));
    result->printable.to_string = (printer)to_string_queue;
    result->elements = make_array(size, elements);
    result->head = result->tail = 0;
    return result;
}

queue make_empty_queue(size_t size) {
    printable** elements = ALLOCATE(sizeof(printable*) * size);
    return make_queue(elements, size);
}
