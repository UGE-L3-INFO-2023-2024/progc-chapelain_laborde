#include "Stats.h"

/* Initialise Statistics of the game to zero */
Stats Stats_init(void) {
    return (Stats){
        .score = 0,
        .total_damage = 0,
        .mana_lost = 0,
        .last_wave = 0,
        .mobs_killed = 0,
        .timeplayed = 0,
    };
}