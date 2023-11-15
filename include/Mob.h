/**
 * @file Mob.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __MOB_H__
#define __MOB_H__

#include "Color.h"
#include "Element.h"

typedef struct {
    unsigned int current_hp;
    unsigned int max_hp;
    unsigned int speed;
    HSV_Color color;
    Element apply_elem;
} Mob;

#endif  // __MOB_H__