#include <string.h>
#include <stdio.h>
#include "printable.h"
#include "generic.h"
#include "query.h"

DEFTYPE(query);

void yyerror(char *text) { fprintf(stderr, "%s\n", text); }

char* to_string_query(query q) {
    if (q == NULL) return "";
    switch (q->kind) {
        case BORROW: {
            const char* pattern = "borrow(patron=%s, id=%s, book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + PATRON_LEN + ID_LEN + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->patron, q->id, q->book_id);
            return result;
        }
        case RETURN: {
            const char* pattern = "return(patron=%s, id=%s, book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + PATRON_LEN + ID_LEN + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->patron, q->id, q->book_id);
            return result;
        }
        case JOIN: {
            const char* pattern = "join(patron=%s, id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + PATRON_LEN + ID_LEN + 1));
            sprintf(result, pattern, q->patron, q->id);
            return result;
        }
        case LEAVE: {
            const char* pattern = "leave(patron=%s, id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + PATRON_LEN + ID_LEN + 1));
            sprintf(result, pattern, q->patron, q->id);
            return result;
        }
        case BOOKS: {
            const char* pattern = "books(id=%s)";
            char* result = ALLOCATE(
                sizeof(char) * (strlen(pattern) + ID_LEN + 1));
            sprintf(result, pattern, q->id);
            return result;
        }
        case WHO_BORROWS: {
            const char* pattern = "who_borrows(book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) * (strlen(pattern) + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->book_id);
            return result;
        }
        case BORROWS_MOST: return "borrow_most()";
    }
    return "Invalid query";
}

query make_query(query_kind kind, char* patron_name, char* patron_id, char* book_id) {
    query result = ALLOCATE(sizeof(printable_query));
    result->kind = kind;
    result->patron = patron_name;
    result->id = patron_id;
    result->book_id = book_id;
    printable* presult = (printable*)result;
    presult->type = query_type();
    define_method(presult->type, to_string, to_string_query);
    return result;
}

void process_query(query q) {
    printf("Processing: %s\n", to_string((printable*)q));
}

char* str(char* in) {
    size_t len = strlen(in);
    char* result = ALLOCATE(sizeof(char) * len + 1);
    strncpy(result, in, len);
    result[len] = '\0';
    return result;
}
