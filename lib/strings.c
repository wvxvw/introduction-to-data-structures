#include "strings.h"

char* join(char** chunks, size_t len, char* separator) {
    if (len == 0) {
        char* empty = ALLOCATE(sizeof(char) * 1);
        empty[0] = '\0';
        return empty;
    }
    if (len == 0) return "";
    size_t i, copied = 0, total = 0, sep_len = strlen(separator);
    size_t* sizes = malloc(sizeof(size_t) * len);
    
    for (i = 0; i < len; i++) {
        size_t s = strlen(chunks[i]);
        sizes[i] = s;
        total += s;
    }
    char* result = ALLOCATE(sizeof(char) * (total + sep_len * (len - 1) + 1));
    for (i = 0; i < len - 1; i++) {
        memcpy(result + copied, chunks[i], sizes[i]);
        copied += sizes[i];
        memcpy(result + copied, separator, sep_len);
        copied += sep_len;
    }
    memcpy(result + copied, chunks[i], sizes[i]);
    copied += sizes[i];
    result[copied] = '\0';
    return result;
}
