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
            const char* pattern = "borrow(actor=%s, id=%s, book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + ACTOR_LEN + ID_LEN + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->actor, q->id, q->book_id);
            return result;
        }
        case RETURN: {
            const char* pattern = "return(actor=%s, id=%s, book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + ACTOR_LEN + ID_LEN + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->actor, q->id, q->book_id);
            return result;
        }
        case JOIN: {
            const char* pattern = "join(actor=%s, id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + ACTOR_LEN + ID_LEN + 1));
            sprintf(result, pattern, q->actor, q->id);
            return result;
        }
        case LEAVE: {
            const char* pattern = "leave(actor=%s, id=%s)";
            char* result = ALLOCATE(
                sizeof(char) *
                (strlen(pattern) + ACTOR_LEN + ID_LEN + 1));
            sprintf(result, pattern, q->actor, q->id);
            return result;
        }
        case BOOKS: {
            const char* pattern = "boks(id=%s)";
            char* result = ALLOCATE(
                sizeof(char) * (strlen(pattern) + ID_LEN + 1));
            sprintf(result, pattern, q->id);
            return result;
        }
        case ACTORID: {
            const char* pattern = "id(book_id=%s)";
            char* result = ALLOCATE(
                sizeof(char) * (strlen(pattern) + BOOK_ID_LEN + 1));
            sprintf(result, pattern, q->book_id);
            return result;
        }
        case BORROWS_MOST: return "borrow_most()";
    }
    return "Invalid query";
}

query make_query(query_kind kind, char* actor_name, char* actor_id, char* book_id) {
    query result = ALLOCATE(sizeof(printable_query));
    result->actor = actor_name;
    result->id = actor_id;
    result->book_id = book_id;
    printable* presult = (printable*)result;
    presult->type = query_type();
    define_method(presult->type, to_string, to_string_query);
    return result;
}
