#ifndef PATH_H
#define PATH_H

#include <stdlib.h>

#include "vector.h"

typedef struct path_t {

    size_t n_points;
    vec2_t *points;
    int order;

} path_t;

path_t *create_path_with_points (size_t n_points, vec2_t *points, int order);
path_t *create_path (size_t n_points, int order);
path_t *copy_path (path_t *path);
void destroy_path_without_points (path_t *path);
void destroy_path (path_t *path);
vec2_t trace_path (path_t *path, double amount);

#endif /* PATH_H */
