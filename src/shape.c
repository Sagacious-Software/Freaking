#include <freaking/shape.h>

#include <kit/region.h>
#include <kit/util.h>

shape_t make_shape (shape_type_t type) {

    shape_t shape;
    shape.type = type;
    return shape;
}

path_t *create_shape_path (shape_t shape) {

    switch (shape.type) {

        case SHAPE_RECTANGLE:
            return create_shape_rectangle_path (shape.shapes.rectangle);

        case SHAPE_VECTOR:
            return create_shape_vector_path (shape.shapes.vector);

        default:
            /* TODO: warning? */
            return create_path (0, 0);
    }
}

void stroke_shape (shape_t shape, buffer_t *buffer, pen_t pen) {

    switch (shape.type) {

        case SHAPE_RECTANGLE:
            stroke_shape_rectangle (shape.shapes.rectangle, buffer, pen);

        case SHAPE_VECTOR:
            stroke_shape_vector (shape.shapes.vector, buffer, pen);

        default:
            /* TODO: warning? */
            return;
    }
}

void fill_shape (shape_t shape, buffer_t *buffer, pen_t pen) {

    switch (shape.type) {

        case SHAPE_RECTANGLE:
            fill_shape_rectangle (shape.shapes.rectangle, buffer, pen);

        case SHAPE_VECTOR:
            fill_shape_vector (shape.shapes.vector, buffer, pen);

        default:
            /* TODO: warning? */
            return;
    }
}

shape_rectangle_t make_shape_rectangle (vec2_t a, vec2_t b) {

    shape_rectangle_t shape;
    shape.a = a;
    shape.b = b;
    return shape;
}

shape_rectangle_t make_shape_rectangle_with_region (region_t region) {

    return make_shape_rectangle (region.offset,
                                 add_vec2 (region.offset, region.dimensions));
}

shape_vector_t make_shape_vector (path_t *path) {

    shape_vector_t shape;
    shape.path = path;
    return shape;
}

path_t *create_shape_rectangle_path (shape_rectangle_t shape) {

    vec2_t *points = calloc (4, sizeof (vec2_t));
    points[0] = shape.a;
    points[1] = make_vec2 (shape.a.x, shape.b.y);
    points[2] = shape.b;
    points[3] = make_vec2 (shape.a.y, shape.b.x);
    return create_path_with_points (4, points, 0);
}

path_t *create_shape_vector_path (shape_vector_t shape) {

    return copy_path (shape.path);
}

void stroke_shape_rectangle (shape_rectangle_t shape, buffer_t *buffer, pen_t pen) {

}

void fill_shape_rectangle (shape_rectangle_t shape, buffer_t *buffer, pen_t pen) {

    int y;
    region_t bounds = make_region (0, 0, buffer->dimensions.x, buffer->dimensions.y);
    vec2_t dimensions = subtract_vec2 (clip_vec2 (shape.b, bounds),
                                       clip_vec2 (shape.a, bounds));
    int line_size = buffer->stride * dimensions.x;
    int bottom = shape.a.y + dimensions.y;

    for (y = shape.a.y; y < bottom; y++) {

        void *destination = get_buffer_address (buffer, make_vec2 (shape.a.x, y));
        memfill (destination, pen.source, line_size, buffer->stride);
    }
}

void stroke_shape_vector (shape_vector_t shape, buffer_t *buffer, pen_t pen) {

}

void fill_shape_vector (shape_vector_t shape, buffer_t *buffer, pen_t pen) {

}
