#include <stdint.h>
#include <stdlib.h>

#include <freaking/util.h>

void *memfill (void *destination,
               void *source,
               size_t destination_size,
               size_t source_size) {

    uint8_t *destination_pointer = (uint8_t *) destination;
    uint8_t *destination_end = destination_pointer + destination_size;
    uint8_t *source_pointer = (uint8_t *) source;
    uint8_t *source_end = source_pointer + source_size;

    while (destination_pointer < destination_end) {

        *(destination_pointer++) = *(source_pointer++);
        if (source_pointer == source_end)
            source_pointer = (uint8_t *) source;
    }

    return destination;
}

double interpolate (double a, double b, double n) {

    return a + (b - a) * n;
}

double modulo (double n, double m) {

    while (n < 0)
        n += m;
    while (n > m)
        n -= m;
    return n;
}
