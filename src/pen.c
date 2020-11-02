#include <freaking/pen.h>

pen_t make_pen (double thickness, void *source) {

    pen_t pen;
    pen.thickness = thickness;
    pen.source = source;
    return pen;
}
