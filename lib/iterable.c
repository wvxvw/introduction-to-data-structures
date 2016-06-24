#include <stdio.h>
#include "printable.h"
#include "array.h"
#include "hashtable.h"
#include "pair.h"
#include "iterable.h"
#include "generic.h"

DEFTYPE(aiterator);
DEFTYPE(hiterator);

bool next(iterator* impl) {
    if (impl == NULL) return false;
    printable* p = (printable*)impl;
    bool (*fptr)(iterator*) = next;
    bool (*method)(iterator*) = find_method(p->type, fptr);
    return method(impl);
}

bool array_next(iterator* impl) {
    array container = (array)impl->iterated;
    size_t pos = ((array_iterator*)impl)->pos + 1;
    bool result = pos < container->length;
    if (result) ((printable*)impl)->val = container->elements[pos];
    return result;
}

bool hashtable_next(iterator* impl) {
    chashtable container = (chashtable)impl->iterated;
    hashtable_iterator* it = (hashtable_iterator*)impl;
    printable* pit = (printable*)impl;
    size_t pos = it->pos;
    list key = (list)it->key;
    list val = (list)it->value;

    if (key == NULL) return false;
    pair kv = make_pair();
    pit->val = kv;
    
    if (key->cdr != NULL){
        it->key = (dlist)key->cdr;
        it->value = (dlist)val->cdr;
        kv->first = key->cdr->car;
        kv->last = val->cdr->car;
        return true;
    }
    pos++;
    while (pos < ((printable*)container)->size) {
        if (container->keys[pos] != NULL) {
            it->key = container->keys[pos];
            it->value = container->values[pos];
            it->pos = pos;
            kv->first = ((list)it->key)->car;
            kv->last = ((list)it->value)->car;
            return true;
        }
        pos++;
    }
    return false;
}

bool has(iterator* impl) {
    if (impl == NULL) return false;
    printable* p = (printable*)impl;
    bool (*fptr)(iterator*) = has;
    bool (*method)(iterator*) = find_method(p->type, fptr);
    return method(impl);
}

bool array_has(iterator* impl) {
    array container = (array)impl->iterated;
    size_t pos = ((array_iterator*)impl)->pos;
    return pos < container->length;
}

bool hashtable_has(iterator* impl) {
    chashtable container = (chashtable)impl->iterated;
    hashtable_iterator* it = (hashtable_iterator*)impl;
    size_t pos = it->pos;
    list key = (list)it->key;

    if (key->cdr != NULL) return true;
    pos++;
    while (pos < ((printable*)container)->size) {
        if (container->keys[pos] != NULL)
            return true;
        pos++;
    }
    return false;
}

iterator* make_array_iterator(array iterated) {
    array_iterator* result = ALLOCATE(sizeof(array_iterator));
    printable* presult = (printable*)result;
    iterator* iresult = (iterator*)result;
    presult->type = aiterator_type();
    define_method(presult->type, next, array_next);
    define_method(presult->type, has, array_has);
    iresult->iterated = (printable*)iterated;
    result->pos = 0;
    presult->val = iterated->elements[result->pos];
    return iresult;
}

iterator* make_hashtable_iterator(chashtable iterated) {
    hashtable_iterator* result = ALLOCATE(sizeof(hashtable_iterator));
    printable* presult = (printable*)result;
    iterator* iresult = (iterator*)result;
    printable* piterated = (printable*)iterated;
    presult->type = hiterator_type();
    define_method(presult->type, next, hashtable_next);
    define_method(presult->type, has, hashtable_has);
    iresult->iterated = (printable*)iterated;
    
    size_t pos = 0;
    while (iterated->keys[pos] == NULL && pos < piterated->size) pos++;
    result->pos = pos;
    if (pos < piterated->size) {
        result->key = iterated->keys[pos];
        result->value = iterated->values[pos];
        pair kv = make_pair();
        kv->first = ((list)result->key)->car;
        kv->last = ((list)result->value)->car;
        presult->val = kv;
    } else {
        result->key = NULL;
        result->value = NULL;
    }
    return iresult;
}
