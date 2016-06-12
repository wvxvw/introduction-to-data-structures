#include <stdio.h>
#include <string.h>
#include "printable.h"
#include "printable_string.h"
#include "list.h"

bool is_alnum(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

list load_words(const unsigned char* file_name) {
#define BUFF_SIZE 255
   FILE* fp;
   char buff[BUFF_SIZE];
   list result = NULL;
   bool finished = false;
   char* prefix = "";
   size_t prefix_len = 0;

   fp = fopen(file_name, "r");

   while (!finished && !feof(fp) && !ferror(fp)) {
       memset(buff, 0, BUFF_SIZE);
       fread(buff, sizeof(char), BUFF_SIZE, fp);
       char current;
       size_t start = 0, word_len, i;
       char* word, *suffix;
       
       for (i = 0; i < BUFF_SIZE; i++) {
           current = buff[i];
           if (current == '\0') {
               finished = true;
               break;
           }
           if (!is_alnum(current)) {
               if (start + 1 < i) {
                   word_len = prefix_len + i - start + 1;
                   suffix = ALLOCATE(sizeof(char) * (i - start));
                   strncpy(suffix, buff + start, i - start);
               } else if (prefix_len > 0) {
                   word_len = prefix_len + 1;
                   suffix = "";
               }
               if (word_len > 1) {
                   word = ALLOCATE(sizeof(char) * word_len);
                   sprintf(word, "%s%s", prefix, suffix);
                   result = cons((printable*)make_printable_string(word), result);
                   prefix_len = 0;
                   prefix = "";
                   word_len = 0;
               }
               start = i + 1;
           }
       }
       if (start + 1 < i) {
           prefix_len = i - start;
           prefix = ALLOCATE(sizeof(char) * prefix_len + 1);
           strncpy(prefix, buff + start, prefix_len);
       }
   }
   fclose(fp);
   return reverse(result);
#undef BUFF_SIZE
}
