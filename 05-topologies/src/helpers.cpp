#include "helpers.hpp"
#include <cstdarg>
#include <cstdio>
#include <time.h>

static struct timespec start_time;

void start_timer() {
    clock_gettime(CLOCK_REALTIME, &start_time);
}

double get_timer()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    double start_sec = start_time.tv_sec + start_time.tv_nsec / 1e9;
    double now_sec = now.tv_sec + now.tv_nsec / 1e9;
    return now_sec - start_sec;
}

void debug(int rank, const char *format, ...)
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