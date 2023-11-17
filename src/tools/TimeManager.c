/**
 * @file Stopwatch.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#include "TimeManager.h"

#include <time.h>

/* Get the interval between two timespec */
int ms_interval(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000000 +
           (end.tv_nsec - start.tv_nsec) / 1000000;
}

/* Convert miliseconds to seconds */
int ms_to_sec(int ms) {
    return ms / 1000;
}
