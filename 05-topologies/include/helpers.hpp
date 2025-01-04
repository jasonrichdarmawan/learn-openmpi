#ifndef HELPERS_H
#define HELPERS_H

void start_timer();

double get_timer();

void debug(int rank, const char *format, ...);

#endif // HELPERS_H