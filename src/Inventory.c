/**
 * @file Inventory.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 11-12-2024
 *
 */
#include "Inventory.h"

#include <stdlib.h>

#include "Error.h"
#include "Gemstone.h"
#include "Mana.h"

Error inventory_init(Inventory* inventory) {
    inventory->gemstones = malloc(sizeof(Gemstone) * 3);
    if (inventory->gemstones == NULL) {
        return MALLOC_ERR;
    }
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 3;
    inventory->mana = Mana_init();
    inventory->fusion[0] = NULL;
    inventory->fusion[1] = NULL;
    return CLEAR;
}

Error inventory_add_gemstone(Inventory* inventory, Gemstone gemstone) {
    if (inventory->gemstones_count == inventory->gemstones_capacity) {
        inventory->gemstones_capacity *= 2;
        inventory->gemstones =
            realloc(inventory->gemstones,
                    sizeof(Gemstone) * inventory->gemstones_capacity);
        if (inventory->gemstones == NULL) {
            return MALLOC_ERR;
        }
    }
    inventory->gemstones[inventory->gemstones_count++] = gemstone;
    return CLEAR;
}

Error inventory_remove_gemstone(Inventory* inventory, Gemstone gemstone) {
    for (int i = 0; i < inventory->gemstones_count; i++) {
        if (Gemstone_equal(inventory->gemstones[i], gemstone)) {
            for (int j = i; j < inventory->gemstones_count - 1; j++) {
                inventory->gemstones[j] = inventory->gemstones[j + 1];
            }
            inventory->gemstones_count--;
            return CLEAR;
        }
    }
    return GEMSTONE_NOT_FOUND;
}

void inventory_free(Inventory* inventory) {
    free(inventory->gemstones);
    inventory->gemstones = NULL;
}