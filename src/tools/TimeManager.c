/**
 * @file TimeManager.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module who help to use timespec struct.
 * @date 16-11-2023
 *
 */

#include "TimeManager.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* Get actual time */
struct timespec Time_get() {
    struct timespec time;
    timespec_get(&time, TIME_UTC);
    return time;
}

/* Transform ms to sec */
static long _ms_to_sec(long ms) {
    return ms / 1000;
}

/* Transform ms to ns */
static long _ms_to_nsec(long ms) {
    // % in case of multiple ms stored.
    return (ms % 1000) * 1000000;
}

/* Get the interval between two timespec */
long Time_ms_interval(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000 +
           (end.tv_nsec - start.tv_nsec) / 1000000;
}

/* Check if a timespec is after another */
bool Time_is_after(struct timespec time, struct timespec to_compare) {
    return Time_ms_interval(time, to_compare) >= 0;
}

/* Add ms to a timespec */
struct timespec Time_add_ms(struct timespec time, long add_ms) {
    return (struct timespec){.tv_sec = time.tv_sec + _ms_to_sec(add_ms),
                             .tv_nsec = time.tv_nsec + _ms_to_nsec(add_ms)};
}

/* Check if a timespec is equal another */
bool Time_is_equal(struct timespec a, struct timespec b) {
    return (a.tv_nsec == b.tv_nsec) && (a.tv_sec == b.tv_sec);
}

/* Print a timespec in ms (debug function) */
void Time_print_ms(struct timespec start) {
    printf("%ld\n", start.tv_nsec / 1000);
}
