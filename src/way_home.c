#include "header.h"

static void remove_all(char *map_str, char c) {
    char *w_ptr = map_str;

    for (int i = 0; map_str[i] != '\0'; i++) {
        if (map_str[i] != c) {
            *w_ptr = map_str[i];
            w_ptr++;
        }
    }

    *w_ptr = '\0';
}

t_map *parse_map(char *map_str) {
    t_map *map = malloc(sizeof(t_map));
    char **rows;

    map->width = 0;
    map->height = 0;

    remove_all(map_str, ',');
    rows = mx_strsplit(map_str, '\n');
    
    for (; rows[map->height] != NULL; map->height++) {
        if (map->width == 0) {
            map->width = mx_strlen(rows[map->height]);
        }
        else if (mx_strlen(rows[map->height]) != map->width) {
            return NULL;
        }
    }

    map->points = arr(map->width, map->height);

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (rows[i][j] == '#') {
                map->points[j][i] = 1; 
            }
            else if (rows[i][j] == '.') {
                map->points[j][i] = 0;                
            }
            else {
                return NULL;
            }
        }
        free(rows[i]);
    }
    free(rows);
    
    return map;
}

bool write_map(const char *filename, t_map *map) {
    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    static const char chars[] = {'.', '#', '*', 'D', 'X'};

    if (file == -1) {
        return false;
    }

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            int idx = map->points[j][i];
            write(file, &chars[idx], 1);
        }
        write(file, "\n", 1);
    }

    close(file);
    return true;
}
