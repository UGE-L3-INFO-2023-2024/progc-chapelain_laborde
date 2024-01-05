/**
 * @file TimeManager.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 16-11-2023
 *
 */
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include <stdbool.h>
#include <time.h>

/*************/
/* Functions */
/*************/

/**
 * @brief Get actual time.
 *
 * @return struct timespec
 */
struct timespec Time_get();

/**
 * @brief Get the interval between two timespec.
 *
 * @param start timespec
 * @param end timespec
 * @return int
 */
long Time_ms_interval(struct timespec start, struct timespec end);

/**
 * @brief Add ms to a timespec.
 *
 * @param time timespec original
 * @param add_ms ms to add
 * @return struct timespec
 */
struct timespec Time_add_ms(struct timespec time, long add_ms);

/**
 * @brief Check if a timespec is after another.
 *
 * @param time timespec
 * @param to_compare timespec
 * @return time > to_compare
 */
bool Time_is_after(struct timespec time, struct timespec to_compare);

/**
 * @brief Print the time given (Debug function).
 *
 * @param start
 */
void Time_print_ms(struct timespec start);

#endif  // __TIME_MANAGER_H__