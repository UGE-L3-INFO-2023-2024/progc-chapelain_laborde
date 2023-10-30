/**
 * @file Wave.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __WAVE_H__
#define __WAVE_H__

#include <sys/time.h>

#include "Mob.h"

typedef struct {
    unsigned int level;
    timeval last_wave_time;
    List mobs;
} Wave;

#endif  // __WAVE_H__