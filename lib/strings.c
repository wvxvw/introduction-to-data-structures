#include "strings.h"

char* join(char** chunks, size_t len, char* separator) {
    if (len == 0) return "";
    size_t i, copied = 0, total = 0, sep_len = strlen(separator);
    
    for (i = 0; i < len; i++) total += strlen(chunks[i]);
    char* result = ALLOCATE(sizeof(char) * (total + sep_len * (len - 1) + 1));
    for (i = 0; i < len - 1; i++) {
        strcpy(result + copied, chunks[i]);
        copied += strlen(chunks[i]);
        strcpy(result + copied, separator);
        copied += sep_len;
    }
    strcpy(result + copied, chunks[i]);
    copied += strlen(chunks[i]);
    result[copied + 1] = '\0';
    return result;
}
