#include <string.h>
#include "library.h"
#include "query.h"
#include "printable_string.h"
#include "generic.h"

DEFTYPE(library);
DEFTYPE(patron);

static library lib;
static patron libpatron;

int compare_patrons(const void* a, const void* b) {
    patron pa = *(patron*)a;
    patron pb = *(patron*)b;

    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    size_t sa = length(pa->books);
    size_t sb = length(pb->books);
    
    return (sa > sb) - (sa < sb);
}

library make_library() {
    library result = ALLOCATE(sizeof(printable_library));
    result->books = make_empty_string_chashtable();
    result->patrons = make_empty_aheap(compare_patrons);
    printable* presult = (printable*)result;
    presult->type = library_type();
    define_method(presult->type, to_string, to_string_library);
    return result;
}

patron make_patron(char* name, char* id) {
    patron result = ALLOCATE(sizeof(printable_patron));
    result->name = name;
    result->id = id;
    result->books = NULL;
    printable* presult = (printable*)result;
    presult->type = patron_type();
    define_method(presult->type, to_string, to_string_patron);
    return result;
}

library get_library() {
    if (lib == NULL) lib = make_library();
    return lib;
}

patron get_libpatron() {
    if (libpatron == NULL) libpatron = make_patron("Library", "******");
    return libpatron;
}

char* library_add_book(library lib, query q) {
    printable_string* book = make_printable_string(q->book_id);
    const char* pattern = "< Added book(%s)\n";
    size_t len = strlen(pattern) + BOOK_ID_LEN + 1;
    char* result = ALLOCATE(sizeof(char) * len);
    library llib = get_library();
    list stored = (list)chashtable_get(llib->books, (printable*)book);

    stored = cons((printable*)book, stored);
    chashtable_put(llib->books, (printable*)book, (printable*)stored);
    sprintf(result, pattern, q->book_id);
    return result;
}

char* library_list_books(library lib, query q) {

    return "< Not implemented\n";
}

char* library_join(library lib, query q) {

    return "< Not implemented\n";
}

char* library_leave(library lib, query q) {

    return "< Not implemented\n";
}

char* library_borrow(library lib, query q) {

    return "< Not implemented\n";
}

char* library_return(library lib, query q) {

    return "< Not implemented\n";
}

char* library_who_borrows(library lib, query q) {

    return "< Not implemented\n";
}

char* library_borrows_most(library lib, query q) {

    return "< Not implemented\n";
}

char* to_string_library(library lib) {
    char* books = to_string((printable*)lib->books);
    char* patrons = to_string((printable*)lib->patrons);
    const char* pattern = "library(books=%s, patrons=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(patrons) - 3;
    char* result = ALLOCATE(sizeof(char) * len);
    sprintf(result, pattern, books, patrons);
    result[len] = '\0';
    return result;
}

char* to_string_patron(patron p) {
    char* books = to_string((printable*)p->books);
    const char* pattern = "patron(books=%s, name=%s, id=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(p->name) + ID_LEN - 3;
    char* result = ALLOCATE(sizeof(char) * len);
    sprintf(result, pattern, books, p->name, p->id);
    result[len] = '\0';
    return result;
}
