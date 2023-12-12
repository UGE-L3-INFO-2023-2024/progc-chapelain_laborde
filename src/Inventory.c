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

void inventory_free(Inventory* inventory) {
    free(inventory->gemstones);
    inventory->gemstones = NULL;
}