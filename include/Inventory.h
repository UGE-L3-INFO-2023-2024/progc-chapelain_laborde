/**
 * @file Inventory.h
 * @author Laborde Quentin
 * @brief  Module to manage the inventory (Init, add, remove, free).
 * @date 11-12-2024
 *
 */

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Error.h"
#include "Gemstone.h"
#include "Mana.h"

#define GEMS_PER_PAGE 12

/**************/
/* Structures */
/**************/

/**
 * @brief The inventory with the gemstones and the mana pool.
 * @todo gemstones must be a dynamic array (DA) ?
 *
 */
typedef struct {
    Gemstone* gemstones;               // The gemstones in the inventory.
    unsigned long gemstones_count;     // The number of gemstones
    unsigned long gemstones_capacity;  // The capacity of the gemstones array.
    Gemstone* fusion[3];               // The two gemstones to fuse and the result.
    struct {                           // The informations about the inventory.
        int page;
        int gem_level;
    } info;
} Inventory;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize an inventory.
 * Allocate memory for 3 gemstones and initialize the mana pool.
 *
 * @param inventory Inventory to initialize.
 *
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error Inventory_init(Inventory* inventory);

/**
 * @brief Add a gemstone to an inventory.
 * If the capacity of the inventory is not enough, it will be reallocated.
 *
 * @param inventory Inventory to add the gemstone to.
 * @param gemstone Gemstone to add.
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error Inventory_add_gemstone(Inventory* inventory, Gemstone gemstone);

/**
 * @brief Free an inventory.
 *
 * @param inventory Inventory to free.
 */
void Inventory_free(Inventory* inventory);

/**
 * @brief Remove a gemstone from the inventory.
 *
 * @param inventory Inventory to remove the gemstone from.
 * @param gemstone Gemstone to remove.
 * @return Error CLEAR if no error occured, GEMSTONE_NOT_FOUND otherwise.
 */
Error Inventory_remove_gemstone(Inventory* inventory, Gemstone gemstone);

#endif  // __INVENTORY_H__