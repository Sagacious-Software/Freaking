#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <freaking/shape.h>
#include <gosh/window.h>
#include <kit/util.h>

typedef struct state_t {

    backend_t *backend;
    window_t *window;
    int i_frame;
    region_t rect_region;
    vec2_t velocity;

} state_t;

void draw (window_t *window, state_t *state) {

    uint32_t packed_color;
    shape_t shape;
    pen_t pen;
    double value;

    if (window->image.buffer == NULL)
        return;

    /* clear the window */
    fill_image (window->image, make_color_rgb (1, 0.5, 0));

    /* animate values */
    value = (sin (state->i_frame++ * 2 * M_PI / 60.0) + 1) / 2.0;
    state->rect_region.offset = add_vec2 (state->rect_region.offset, state->velocity);

    /* TODO: clean this up very much */
    /* bounce the rectangle */
    if ((state->velocity.x > 0 && state->rect_region.offset.x + state->rect_region.dimensions.x >= window->region.dimensions.x) ||
        (state->velocity.x < 0 && state->rect_region.offset.x <= 0))
        state->velocity.x *= -1;
    if ((state->velocity.y > 0 && state->rect_region.offset.y + state->rect_region.dimensions.y >= window->region.dimensions.y) ||
        (state->velocity.y < 0 && state->rect_region.offset.y <= 0))
        state->velocity.y *= -1;

    /* draw a rectangle or smth, like yaaa, Ugh */
    pack_color (window->image.format, &packed_color, make_color_rgb (value, 0, 0));
    pen = make_pen (0, &packed_color);
    shape = make_shape (SHAPE_RECTANGLE);
    shape.shapes.rectangle = make_shape_rectangle_with_region (state->rect_region);
    fill_shape (shape, window->image.buffer, pen);

    update_window (window);
}

void callback (window_t *window, event_t event, void *data) {

    state_t *state = (state_t *) data;

    switch (event.type) {

        case EVENT_VBLANK:

            draw (window, state);

            break;

        case EVENT_DESTROY:

            backend_exit (window->backend);

            break;

        case EVENT_KEYBOARD:

            if (event.events.keyboard.key == KEYBOARD_KEY_ESCAPE)
                close_window (window);

            break;

        default:
            break;
    }
}

int main (int argc, char **argv) {

    state_t state;
    region_t region = make_region (0, 0, 400, 300);

    /* initialize animation state */
    state.i_frame = 0;
    state.rect_region = make_region (10, 10, 100, 50);
    state.velocity = make_vec2 (5, 5);

    if ((state.backend = create_backend (BACKEND_AUTO)) == NULL) {

        fputs ("Failure to create Gosh backend.\n", stderr);
        return EXIT_FAILURE;
    }

    if ((state.window = create_window (state.backend, region, "Freaking Demo", callback, &state)) == NULL) {

        fputs ("Failure to create Gosh window.\n", stderr);
        return EXIT_FAILURE;
    }

    backend_run (state.backend, NULL, NULL);

    destroy_window (state.window);
    destroy_backend (state.backend);

    return EXIT_SUCCESS;
}
