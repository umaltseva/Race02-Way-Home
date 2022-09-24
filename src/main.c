#include "../inc/header.h"

static bool check_bounds(t_map *map, t_point *point) {
    return point->x >= 0
        && point->y >= 0
        && point->x < map->width
        && point->y < map->height;
}

int main(int argc, char *argv[]) {
    if (argc != 6 ) {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        return -1;
    }

    char *map_str = mx_file_to_str(argv[1]);
    bool status = true;
    t_map *map;
    t_point *entry;
    t_point *exit;

    if (map_str == NULL
        || mx_strlen(map_str) == 0) {
        mx_printerr("map does not exist\n");
        status = false;
    }

    if (status) {
        map = parse_map(map_str);
        if (map == NULL) {
            mx_printerr("map error\n");
            status = false;
        }
    }

    if (status) {
        entry = new_point(mx_atoi(argv[2]), mx_atoi(argv[3]));
        exit = new_point(mx_atoi(argv[4]), mx_atoi(argv[5]));

        if (!check_bounds(map, entry)
            || !check_bounds(map, exit)) {
            mx_printerr("points are out of map range\n");
            status = false;
        }
    }

    if (status
        && map->points[entry->x][entry->y] == 1) {
        mx_printerr("entry point cannot be an obstacle\n");
        status = false;
    }

    if (status
        && map->points[exit->x][exit->y] == 1) {
        mx_printerr("exit point cannot be an obstacle\n");
        status = false;
    }

    if (status) {
        int **temp = map->points;
        map->points = lee(map, entry);
        t_list *path = find_path(map, exit);
        t_list *max = get_max_distance(map);

        if (path == NULL) {
            mx_printerr("route not found\n");
            status = false;
        }
        else {
            t_point *max_point = (t_point*)max->data;

            mx_printstr("dist=");
            mx_printint(map->points[max_point->x][max_point->y]);
            mx_printstr("\n");
            mx_printstr("exit=");
            mx_printint(mx_list_size(path) - 1);
            mx_printstr("\n");

            map->points = temp;

            while (path != NULL) {
                t_point *point = (t_point*)path->data;

                map->points[point->x][point->y] = 2;
                free(point);
                path = path->next;
            }
            mx_clear_list(&path);

            while (max != NULL) {
                t_point *point = (t_point*)max->data;
                
                if (map->points[point->x][point->y] == 2) {
                    map->points[point->x][point->y] = 4;
                }
                else {
                    map->points[point->x][point->y] = 3;
                }

                free(point);
                max = max->next;
            }
            mx_clear_list(&max);
        }
    }
        
    if (status
        && !write_map("path.txt", map)) {
        mx_printerr("error\n");
    }

    free(map_str);
    free(entry);

    for (int i = 0; i < map->width; i++) {
        free(map->points[i]);
    }
    free(map->points);
}


