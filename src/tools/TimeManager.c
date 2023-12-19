/**
 * @file Stopwatch.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#include "TimeManager.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

static long _ms_to_sec(long ms) {
    return ms / 1000;
}

static long _ms_to_nsec(long ms) {
    return (ms % 1000) * 1000000;
}

void Time_print_ms(struct timespec start) {
    printf("%ld\n", start.tv_nsec / 1000);
    // printf("%lld\n", start.tv_sec * 1000 + start.tv_nsec / 1000);
}

long Time_ms_interval(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000 +
           (end.tv_nsec - start.tv_nsec) / 1000000;
}

bool Time_is_after(struct timespec time, struct timespec to_compare) {
    return Time_ms_interval(time, to_compare) >= 0;
}

struct timespec Time_add_ms(struct timespec time, long add_ms) {
    return (struct timespec){.tv_sec = time.tv_sec + _ms_to_sec(add_ms),
                             .tv_nsec = time.tv_nsec + _ms_to_nsec(add_ms)};
}
