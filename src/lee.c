#include "header.h"

t_point *new_point(int x, int y) {
    t_point *point = malloc(sizeof(t_point));

    point->x = x;
    point->y = y;

    return point;
}

int **arr(int row, int col) {
    int **array;

    array = malloc(sizeof(int*) * row);

    for (int i = 0; i < row; i++) {
        array[i] = malloc(sizeof(int) * col);
        
        for (int j = 0; j < col; j++) {
            array[i][j] = -1;
        }
    }
    return array;
}


int **lee(t_map *map, t_point *entry) {
    t_list *queue = NULL;
    int **dist = arr(map->width, map->height);
    static const t_point offsets[] = {
        {-1, 0},
        {0, -1},
        {0, 1},
        {1, 0},
    };


    mx_push_back(&queue, new_point(entry->x, entry->y));
    dist[entry->x][entry->y] = 0;

    while (mx_list_size(queue) != 0) {
        t_point *point = (t_point*)queue->data;
        mx_pop_front(&queue);

        for (int i = 0; i < 4; i++) {
            t_point *temp = new_point(point->x + offsets[i].x,
                                       point->y + offsets[i].y); 
            if (point->x < 0
                || temp->y < 0
                || temp->x >= map->width
                || temp->y >= map->height
                || map->points[temp->x][temp->y] == 1
                || dist[temp->x][temp->y] != -1) {
                free(temp);
                continue;
            }

            dist[temp->x][temp->y] = dist[point->x][point->y] + 1;
            mx_push_back(&queue, temp);
        }
        
    }
    
    return dist;
}


