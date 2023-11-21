/**
 * @file Tower.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#define _XOPEN_SOURCE 600

#include "Tower.h"

#include <time.h>

#include "TimeManager.h"

/* Create a tower object */
Tower Tower_init(Coord_i coord) {
    Tower tower;
    tower.gem = NULL;
    tower.available_at = (struct timespec){0, 0};
    tower.coord = coord;
    return tower;
}

/* Add gem to a tower */
int Tower_add_gem(Tower* tower, Gem* gem) {
    if (!tower || !gem) {
        return 0;
    }
    tower->gem = gem;
    clock_gettime(CLOCK_REALTIME, &tower->available_at);
    tower->available_at.tv_sec += 2;
    return 1;
}

/* Extract gem from a tower */
Gem* Tower_extract_gem(Tower* tower) {
    if (!tower || !tower->gem) {
        return NULL;
    }
    Gem* gem = tower->gem;
    tower->gem = NULL;
    return gem;
}
