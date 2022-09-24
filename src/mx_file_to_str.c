#include "header.h"

static void strdel(char *str) {
    if (str != NULL) {
        free(str);
    }
}

char *mx_file_to_str(const char *filename) {
    char *str = NULL;
    char *buf = mx_strnew(128);
    int file = open(filename, O_RDONLY);
    ssize_t result = 0;

    if (file != -1) {
        while ((result = read(file, buf, 128)) > 0) {
            char *temp = str;
            
            buf[result] = '\0';
            str = mx_strjoin(str, buf);
            strdel(temp);
        }
        close(file);
    }

    strdel(buf);
    
    if (result == -1) {
        strdel(str);
        str = NULL;
    }
    return str;
}
