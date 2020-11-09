#ifndef SHAPE_H
#define SHAPE_H

#include <kit/vector.h>
#include <kit/buffer.h>
#include <kit/region.h>
#include "path.h"
#include "pen.h"

typedef enum shape_type_t {

    SHAPE_RECTANGLE,
    SHAPE_VECTOR,

    NUM_SHAPE_TYPE

} shape_type_t;

typedef struct shape_rectangle_t {

    /* two opposing corners defining the rectangle */
    vec2_t a;
    vec2_t b;

} shape_rectangle_t;

typedef struct shape_vector_t {

    path_t *path;

} shape_vector_t;

typedef struct shape_t {

    shape_type_t type;

    union {

        shape_rectangle_t rectangle;
        shape_vector_t vector;

    } shapes;

} shape_t;

shape_t make_shape        (shape_type_t type);
path_t *create_shape_path (shape_t shape);

void stroke_shape (shape_t shape, buffer_t *buffer, pen_t pen);
void fill_shape   (shape_t shape, buffer_t *buffer, pen_t pen);

shape_rectangle_t make_shape_rectangle             (vec2_t a, vec2_t b);
shape_rectangle_t make_shape_rectangle_with_region (region_t region);
shape_vector_t    make_shape_vector                (path_t *path);

path_t *create_shape_rectangle_path (shape_rectangle_t shape);
path_t *create_shape_vector_path    (shape_vector_t shape);

void stroke_shape_rectangle (shape_rectangle_t shape, buffer_t *buffer, pen_t pen);
void fill_shape_rectangle   (shape_rectangle_t shape, buffer_t *buffer, pen_t pen);

void stroke_shape_vector (shape_vector_t shape, buffer_t *buffer, pen_t pen);
void fill_shape_vector   (shape_vector_t shape, buffer_t *buffer, pen_t pen);

#endif /* SHAPE_H */
