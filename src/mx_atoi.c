#include "header.h"

static bool mult_with_overflow(long *a, long b) {
    long result = 9223372036854775807 / b;

    if (result < *a) {
        return true;
    }

    *a *= b;
    return false;
}

static bool add_with_overflow(long *a, long b) {
    long result = 9223372036854775807 - b;

    if (result < *a) {
        return true;
    }

    *a += b;
    return false;
}

int mx_atoi(const char *str) {
    long result = 0;
    bool negative = false;

    while (mx_isspace(*str)) {
        str++;
    }

    if (*str == '-'
        || *str == '+') {
        if (*str == '-') {
            negative = true;
        }
        str++;
    }

    while (mx_isdigit(*str)) {
        if (mult_with_overflow(&result, 10)
            || add_with_overflow(&result, (*str - 48))) {
            return negative ? 0 : -1;
        }
        str++;
    }

    return negative ? -result : result;
}
