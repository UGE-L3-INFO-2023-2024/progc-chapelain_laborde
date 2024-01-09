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
    Error error = (Error){__func__, CLEAR};
    inventory->gemstones = malloc(sizeof(Gemstone) * 3);
    if (inventory->gemstones == NULL) {
        error.type = MALLOC_ERR;
        return error;
    }
    inventory->gemstones_count = 0;
    inventory->gemstones_capacity = 3;
    inventory->mana = Mana_init();
    inventory->fusion[0] = NULL;
    inventory->fusion[1] = NULL;
    return error;
}

Error inventory_add_gemstone(Inventory* inventory, Gemstone gemstone) {
    Error error = (Error){__func__, CLEAR};
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
    return error;
}

Error inventory_remove_gemstone(Inventory* inventory, Gemstone gemstone) {
    Error error = (Error){__func__, CLEAR};
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
    return error;
}

void inventory_free(Inventory* inventory) {
    free(inventory->gemstones);
    inventory->gemstones = NULL;
}