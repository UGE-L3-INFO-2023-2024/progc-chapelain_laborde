/**
 * @file Inventory.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the inventory (Init, add, remove, free).
 * @date 11-12-2024
 *
 */
#include "Inventory.h"

#include <stdlib.h>

#include "Error.h"
#include "Gemstone.h"
#include "Mana.h"

/* Initialise the inventory */
Error Inventory_init(Inventory* inventory) {
    Error error = NO_ERROR;
    inventory->gemstones = malloc(sizeof(Gemstone) * 3);
    if (inventory->gemstones == NULL) {
        error.type = MALLOC_ERR;
        return error;
    }
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 3;
    for (int i = 0; i < 3; i++) {
        inventory->fusion[i] = NULL;
    }
    inventory->info.page = 0;
    inventory->info.gem_level = 0;
    return NO_ERROR;
}

/* Add gems to inventory (realloc inside) */
Error Inventory_add_gemstone(Inventory* inventory, Gemstone gemstone) {
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

/* Remove a gem from inventory */
Error Inventory_remove_gemstone(Inventory* inventory, Gemstone gemstone) {
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

/* Free the inventory */
void Inventory_free(Inventory* inventory) {
    free(inventory->gemstones);
    inventory->gemstones = NULL;
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 0;
    for (int i = 0; i < 3; i++) {
        free(inventory->fusion[i]);
        inventory->fusion[i] = NULL;
    }
    inventory->info.page = 0;
    inventory->info.gem_level = 0;
}