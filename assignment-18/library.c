#include <string.h>
#include "library.h"
#include "query.h"
#include "printable_string.h"
#include "generic.h"
#include "sortable.h"

DEFTYPE(library);
DEFTYPE(patron);

static library lib = NULL;
static patron libpatron = NULL;

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

int compare_patron_ids(const void* a, const void* b) {
    patron pa = *(patron*)a;
    patron pb = *(patron*)b;

    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    return strcmp(pa->id, pb->id);
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
    patron lpatron = get_libpatron();
    list stored = (list)chashtable_get(llib->books, (printable*)book);

    stored = cons((printable*)lpatron, stored);
    chashtable_put(llib->books, (printable*)book, (printable*)stored);
    sprintf(result, pattern, q->book_id);
    return result;
}

char* library_list_books(library lib, query q) {

    return "< library_list_books: Not implemented\n";
}

char* library_join(library lib, query q) {
    patron p = make_patron(q->patron, q->id);
    patron existing = (patron)find(
        lib->patrons, (printable*)p, compare_patron_ids);
    char* result, *pattern;
    
    if (existing == NULL) {
        aput(lib->patrons, (printable*)p);
        pattern = "< Registering %s\n";
    } else pattern = "< Patron %s already registered\n";
    result = ALLOCATE(
        sizeof(char) * (strlen(pattern) + strlen(q->id) + 1));
    int ret = sprintf(result, pattern, q->id);
    if (ret < 0) printf("Error printing library_join\n");
    return result;
}

char* library_leave(library lib, query q) {

    return "< library_leave: Not implemented\n";
}

char* library_borrow(library lib, query q) {

    return "< library_borrow: Not implemented\n";
}

char* library_return(library lib, query q) {

    return "< library_return: Not implemented\n";
}

char* library_who_borrows(library lib, query q) {

    return "< library_who_borrows: Not implemented\n";
}

char* library_borrows_most(library lib, query q) {

    return "< library_borrows_most: Not implemented\n";
}

char* library_show(library lib, query q) {
    char* slib = to_string((printable*)get_library());
    size_t len = strlen(slib) + 4;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, "< %s\n", slib);
    if (ret < 0) printf("Error showing library\n");
    return result;
}

char* to_string_library(library llib) {
    char* books = to_string((printable*)llib->books);
    char* patrons = to_string((printable*)llib->patrons);
    const char* pattern = "library(books=%s, patrons=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(patrons) + 1;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, books, patrons);
    if (ret < 0) printf("Error printing library\n");
    return result;
}

char* to_string_patron(patron p) {
    char* books = to_string((printable*)p->books);
    const char* pattern = "patron(books=%s, name=%s, id=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(p->name) + ID_LEN - 3;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, books, p->name, p->id);
    if (ret < 0) printf("Error printing patron\n");
    return result;
}
