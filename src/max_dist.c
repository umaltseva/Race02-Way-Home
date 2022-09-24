#include "header.h"

t_list *get_max_distance(t_map *map) {
    t_list *list = NULL;
    int max = -1;
    
    for (int i = 0; i < map->width; i++){
        for (int j = 0; j < map->height; j++) {
            if (map->points[i][j] > max) {
                max = map->points[i][j];
            }
        }
    }

    if (max == -1) {
        return NULL;
    }

    for (int i = 0; i < map->width; i++){
        for (int j = 0; j < map->height; j++) {
            if (max == map->points[i][j]) {
                mx_push_back(&list, new_point(i, j));                
            }
        }
    }

    return list;
}
