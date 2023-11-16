/**
 * @file Tower.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#include "Tower.h"

Tower Tower_init(Gem* gem, Coord_i coord) {
    Tower tower;
    tower.gem = gem;
    tower.coord = coord;
    return tower;
}