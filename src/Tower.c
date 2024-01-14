/**
 * @file Tower.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage tower. (creation, gems)
 * @date 16-11-2023
 *
 */

#include "Tower.h"

#include <stdbool.h>
#include <stdlib.h>

#include "Gemstone.h"
#include "TimeManager.h"

/* Create a tower object */
Tower Tower_init(Coord_i coord) {
    Tower tower;
    tower.has_gem = false;
    tower.available_at = Time_get();
    tower.coord = coord;
    return tower;
}

/* Add gem to a tower */
bool Tower_add_gem(Tower* tower, Gem* gem) {
    if (!tower || !gem) {
        return false;
    }
    tower->gem = Gemstone_copy(gem);
    tower->has_gem = true;
    tower->available_at = Time_add_ms(Time_get(), TOWER_GEM_COOLDOWN_MS);
    return true;
}

/* Extract gem from a tower */
bool Tower_extract_gem(Tower* tower, Gem* gem) {
    if (!tower || !tower->has_gem) {
        return false;
    }
    if (gem) {
        *gem = Gemstone_copy(&tower->gem);
    }
    tower->has_gem = false;
    return true;
}
