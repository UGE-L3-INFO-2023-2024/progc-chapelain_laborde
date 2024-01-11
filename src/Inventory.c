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
    Error error = NO_ERROR;
    inventory->gemstones = malloc(sizeof(Gemstone) * 3);
    if (inventory->gemstones == NULL) {
        error.type = MALLOC_ERR;
        return error;
    }
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 3;
    inventory->fusion[0] = NULL;
    inventory->fusion[1] = NULL;
    inventory->fusion[2] = NULL;
    inventory->info.page = 0;
    inventory->info.gem_level = 0;
    return NO_ERROR;
}

Error inventory_add_gemstone(Inventory* inventory, Gemstone gemstone) {
    Error error = NO_ERROR;
    if (inventory->gemstones_count == inventory->gemstones_capacity) {
        inventory->gemstones_capacity *= 2;
        inventory->gemstones =
            realloc(inventory->gemstones,
                    sizeof(Gemstone) * inventory->gemstones_capacity);
        if (inventory->gemstones == NULL) {
            error.type = MALLOC_ERR;
            return error;
        }
    }
    inventory->gemstones[inventory->gemstones_count++] = gemstone;
    return NO_ERROR;
}

Error inventory_remove_gemstone(Inventory* inventory, Gemstone gemstone) {
    Error error = NO_ERROR;
    for (int i = 0; i < inventory->gemstones_count; i++) {
        if (Gemstone_equal(inventory->gemstones[i], gemstone)) {
            for (int j = i; j < inventory->gemstones_count - 1; j++) {
                inventory->gemstones[j] = inventory->gemstones[j + 1];
            }
            inventory->gemstones_count--;
            return error;
        }
    }
    error.type = GEMSTONE_NOT_FOUND;
    return NO_ERROR;
}

void inventory_free(Inventory* inventory) {
    free(inventory->gemstones);
    inventory->gemstones = NULL;
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 0;
    free(inventory->fusion[0]);
    free(inventory->fusion[1]);
    inventory->fusion[0] = NULL;
    inventory->fusion[1] = NULL;
    inventory->info.page = 0;
    inventory->info.gem_level = 0;
}