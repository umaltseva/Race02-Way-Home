#include "header.h"

t_list *find_path(t_map *map, t_point *exit) {
    static const t_point offsets[] = {
        {-1, 0},
        {0, -1},
        {0, 1},
        {1, 0},
    };
    t_list *path = NULL;
    t_point *current = exit;

    if (map->points[exit->x][exit->y] == -1) {
        return NULL;
    }

    mx_push_back(&path, exit);

    while (map->points[current->x][current->y] != 0) {        
        for (int i = 0; i < 4; i++) {
            t_point *temp = new_point(current->x + offsets[i].x,
                                      current->y + offsets[i].y);

            if (map->points[temp->x][temp->y]
                < map->points[current->x][current->y]
                && map->points[temp->x][temp->y] != -1) {
                mx_push_back(&path, temp);
                current = temp;
                break;
            }
            
            free(temp);
        }
    }
    
    return path;
}
