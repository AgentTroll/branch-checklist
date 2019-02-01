#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include "util.h"

char *concat(const char *a, const char *b) {
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);

    char *final_str = (char *) malloc(a_len + b_len + 1);
    memcpy(final_str, a, a_len);
    memcpy(final_str + a_len, b, b_len + 1);

    return final_str;
}

int ends_with(const char *test, const char *end) {
    size_t test_len = strlen(test);
    size_t end_len = strlen(end);
    if (end_len > test_len) {
        return FALSE;
    }

    for (size_t end_idx = 0, test_idx = test_len - end_len;
         end_idx < end_len;
         end_idx++, test_idx++) {
        char end_c = *(end + end_idx);
        char test_c = *(test + test_idx);

        if (end_c != test_c) {
            return FALSE;
        }
    }

    return TRUE;
}

int begins_with(const char *test, const char *begin) {
    int offset = 0;
    for (size_t idx = 0; ; idx++) {
        char test_c = *(test + idx);
        if (test_c == ' ') {
            offset++;
            continue;
        }

        char begin_c = *(begin + idx - offset);
        if (begin_c == '\0') {
            break;
        }

        if (test_c == '\0') {
            return FALSE;
        }

        if (begin_c != test_c) {
            return FALSE;
        }
    }

    return TRUE;
}
