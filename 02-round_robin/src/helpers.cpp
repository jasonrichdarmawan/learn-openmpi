#include "helpers.hpp"
#include <cstdarg>
#include <cstdio>
#include <time.h>

// Get the current time in seconds with nanosecond precision
static double get_timer()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void debug(int rank, char *format, ...)
{
    va_list args; /* Variable argument list */

    /* Initialize variable argument list;
       `format` is last argument before `...` */
    va_start(args, format);

    printf("%12.6f|%2d|", get_timer(), rank);
    vprintf(format, args);

    /* Clean up variable argument list */
    va_end(args);
}