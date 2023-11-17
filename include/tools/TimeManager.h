/**
 * @file Stopwatch.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include <time.h>

/**
 * @brief Get the interval between two timespec
 *
 * @param start timespec
 * @param end timespec
 * @return int
 */
int ms_interval(struct timespec start, struct timespec end);

#endif  // __TIME_MANAGER_H__