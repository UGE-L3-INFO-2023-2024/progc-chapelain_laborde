/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#include "../include/Mana.h"

#include <math.h>

ManaPool Init_mana(void) {
    return (ManaPool){
        .level = 0,
        .mana_real = MANA_START,
        .mana_max = Mana_max(0),
    };
}

int Mana_max(int level) {
    return 2000 * pow(1.4, level);
}