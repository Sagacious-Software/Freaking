#include <stdlib.h>

#include <freaking/path.h>

path_t *create_path_with_points (size_t n_points, vec2_t *points, int order) {

    path_t *path = malloc (sizeof (path_t));
    path->n_points = n_points;
    path->points = points;
    path->order = order;
    return path;
}

path_t *create_path (size_t n_points, int order) {

    vec2_t *points = calloc (n_points, sizeof (vec2_t));
    return create_path_with_points (n_points, points, order);
}

path_t *copy_path (path_t *path) {

    int i;
    path_t *copy = create_path (path->n_points, path->order);

    for (i = 0; i < path->n_points; i++)
        copy->points[i] = path->points[i];

    return copy;
}

void destroy_path_without_points (path_t *path) {

    free (path);
}

void destroy_path (path_t *path) {

    free (path->points);
    destroy_path_without_points (path);
}

vec2_t trace_path (path_t *path, double amount) {

    double scaled = amount * (path->n_points - 1);
    int i = scaled;
    double segment_amount = scaled - i;

    /* TODO: higher order curves */

    vec2_t a = path->points[i];
    vec2_t b = path->points[i + 1];
    return interpolate_vec2 (a, b, segment_amount);
}
