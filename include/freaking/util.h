#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

/* fill destination memory with a repeating pattern copied from source */
void *memfill (void *destination,
               void *source,
               size_t destination_size,
               size_t source_size);

/* interpolate between two values */
double interpolate (double a, double b, double n);

/* real modulo */
double modulo (double n, double m);

/* https://stackoverflow.com/a/3437433 */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#endif /* UTIL_H */
