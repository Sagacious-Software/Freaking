#ifndef PEN_H
#define PEN_H

typedef struct pen_t {

    double thickness;
    void *source; /* the pixel value to paint with */

    /* TODO: line styles and stuff probably */

} pen_t;

pen_t make_pen (double thickness, void *source);

#endif /* PEN_H */
