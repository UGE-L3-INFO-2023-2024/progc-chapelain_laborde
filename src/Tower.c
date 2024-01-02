/**
 * @file Tower.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#include "Tower.h"

#include <stdlib.h>

#include "Gemstone.h"
#include "TimeManager.h"

/* Create a tower object */
Tower Tower_init(Coord_i coord) {
    Tower tower;
    tower.gem = NULL;
    tower.available_at = Time_get();
    tower.coord = coord;
    return tower;
}

/* Add gem to a tower */
int Tower_add_gem(Tower* tower, Gem* gem) {
    if (!tower || !gem) {
        return 0;
    }
    tower->gem = gem;
    tower->available_at = Time_add_ms(Time_get(), TOWER_GEM_COOLDOWN_MS);
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
