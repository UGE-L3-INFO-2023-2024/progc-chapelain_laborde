#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Error.h"
#include "Gemstone.h"
#include "Mana.h"

typedef struct {
    Gemstone* gemstones;
    unsigned long gemstones_count;
    unsigned long gemstones_capacity;
    ManaPool mana;
} Inventory;

/**
 * @brief Initialize an inventory.
 * Allocate memory for 3 gemstones and initialize the mana pool.
 *
 * @param inventory Inventory to initialize.
 *
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error inventory_init(Inventory* inventory);

/**
 * @brief Add a gemstone to an inventory.
 * If the capacity of the inventory is not enough, it will be reallocated.
 *
 * @param inventory Inventory to add the gemstone to.
 * @param gemstone Gemstone to add.
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error inventory_add_gemstone(Inventory* inventory, Gemstone gemstone);

/**
 * @brief Free an inventory.
 *
 * @param inventory Inventory to free.
 */
void inventory_free(Inventory* inventory);

#endif  // __INVENTORY_H__