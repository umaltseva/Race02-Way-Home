#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "list.h"

typedef struct s_point {
    int x;
    int y;
}              t_point;

typedef struct s_map {
    int width;
    int height;
    int **points;
}              t_map;

int mx_atoi(const char *str);
char *mx_file_to_str(const char *filename);
void mx_printchar(char c);
void mx_printerr(const char *s);
void mx_printint(int n);
void mx_printstr(const char *s);
char *mx_strjoin(char const *s1, char const *s2);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
int mx_count_words(const char *str, char delimiter);
char *mx_strncpy(char *dst, const char *src, int len);
char **mx_strsplit(char const *s, char c);
char *mx_strdup(const char *str);
char *mx_strcpy(char *dst, const char *src);
char *mx_strcat(char *s1, const char *s2);
bool mx_isdigit(int c);
bool mx_isspace(char c);
t_map *parse_map(char *map_str);
t_point *new_point(int x, int y);
int **lee(t_map *map, t_point *entry);
t_list *get_max_distance(t_map *map);
t_list *find_path(t_map *map, t_point *exit);
int **arr(int row, int col);
bool write_map(const char *filename, t_map *map);
