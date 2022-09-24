#include "header.h"

char *mx_strdup(const char *str) {
    char *new_str;

    if (str == 0) {
        return 0;
    }

    new_str = mx_strnew(mx_strlen(str));

    if (new_str == 0) {
        return 0;
    }

    return mx_strcpy(new_str, str);
}
