/**
 * @file DragAndDrop.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to handle drag and drop events on gemstones
 * @date 10-01-2024
 *
 */

#include "DragAndDrop.h"

#include <stdbool.h>
#include <stdlib.h>

#include "Event.h"
#include "FieldEvent.h"
#include "Game.h"
#include "Gemstone.h"
#include "InventoryEvent.h"
#include "Tower.h"
#include "Utils.h"

/**
 * @brief Check if the a gemstone is clicked on the inventory.
 * If is the case, the gemstone is removed from the inventory and
 * the pointer to the gemstone is returned in clicked_gem.
 *
 * @param game The game structure
 * @param event The event to check
 * @param clicked_gem The pointer to the gemstone clicked
 * @return true If a gemstone is clicked on the inventory
 */
static bool drag_gemstone_from_inventory(Game* game, Event event,
                                         Gem** clicked_gem) {
    Gem* temp;
    if ((temp =
             click_on_gemstone(game->window.inventory, event, game->inventory,
                               game->inventory.info.page)) != NULL) {
        *clicked_gem = Gemstone_copy_ptr(temp);
        inventory_remove_gemstone(&game->inventory, *temp);
        return true;
    }
    return false;
}

/**
 * @brief Check if the a gemstone is clicked on a tower.
 * If is the case, the gemstone is removed from the tower and
 * the pointer to the gemstone is returned in clicked_gem.
 * We also save the pointer to the tower in clicked_tower to
 * be able to put the gemstone back on the tower if the player don't drop it at
 * a valid place.
 *
 * @param game The game structure
 * @param event The event to check
 * @param clicked_gem The pointer to the gemstone clicked
 * @param clicked_tower The pointer to the tower clicked
 * @return true If a tower is clicked and has a gemstone
 */
static bool drag_gemstone_from_tower(Game* game, Event event,
                                     Gem** clicked_gem,
                                     Tower** clicked_tower) {
    *clicked_tower = click_on_tower(game->window.map, event, game->map);
    if (*clicked_tower != NULL && (*clicked_tower)->has_gem) {
        *clicked_gem = Gemstone_copy_ptr(&(*clicked_tower)->gem);
        Tower_extract_gem(*clicked_tower, *clicked_gem);
        return true;
    }
    return false;
}

/**
 * @brief Check if the a gemstone is clicked on a fusion slot.
 * If is the case, the gemstone is removed from the fusion slot and
 * a pointer to the gemstone is returned in clicked_gem.
 *
 * @param game The game structure
 * @param event The event to check
 * @param clicked_gem The pointer to the gemstone clicked
 * @return true If a fusion slot is clicked and has a gemstone in it.
 */
static bool drag_gemstone_from_fusion(Game* game, Event event,
                                      Gem** clicked_gem) {
    int slot = click_on_fusion_slot(game->window.inventory, event);
    if (slot != -1 && game->inventory.fusion[slot] != NULL) {
        *clicked_gem = Gemstone_copy_ptr(game->inventory.fusion[slot]);
        free(game->inventory.fusion[slot]);
        game->inventory.fusion[slot] = NULL;
        if (slot == 2 && game->inventory.fusion[0] != NULL &&
            game->inventory.fusion[1] != NULL) {
            free(game->inventory.fusion[0]);
            free(game->inventory.fusion[1]);
            game->inventory.fusion[0] = NULL;
            game->inventory.fusion[1] = NULL;
        }
        return true;
    }
    return false;
}

/**
 * @brief Check if the player drop the gemstone on a tower.
 * If is the case, the gemstone is added to the tower.
 * If the tower already has a gemstone, the gemstone is put back in the
 * inventory.
 *
 * @param game The game structure
 * @param event The event to check
 * @param clicked_gem The pointer to the gemstone clicked
 * @param is_dragging The pointer to the boolean is_dragging to know if the
 * player is dragging a gemstone or not
 * @return true If the player drop the gemstone on a tower
 */
static bool drop_gemstone_on_tower(Game* game, Event event, Gem** clicked_gem,
                                   bool* is_dragging) {
    Tower* hovered_tower =
        get_hovered_tower(game->window.map, event, game->map);
    if (drop_item(event, is_dragging) && hovered_tower != NULL) {
        if (hovered_tower->has_gem) {
            Gem tower_gem;
            Tower_extract_gem(hovered_tower, &tower_gem);
            inventory_add_gemstone(&game->inventory, tower_gem);
        }
        Tower_add_gem(hovered_tower, *clicked_gem);
        *clicked_gem = NULL;
        *is_dragging = false;
        return true;
    }
    return false;
}

/**
 * @brief Check if the player drop the gemstone on a fusion slot.
 * If is the case, the gemstone is added to the fusion slot.
 * If the fusion slot already has a gemstone, the gemstone is put back in the
 * inventory.
 *
 * @param game The game structure
 * @param event The event to check
 * @param clicked_gem The pointer to the gemstone clicked
 * @param is_dragging The pointer to the boolean is_dragging to know if the
 * player is dragging a gemstone or not
 * @return true If the player drop the gemstone on a fusion slot
 */
static bool drop_gemstone_on_fusion_slot(Game* game, Event event,
                                         Gem** clicked_gem,
                                         bool* is_dragging) {
    int slot = get_hovered_fusion_slot(game->window.inventory, event);
    if (drop_item(event, is_dragging) && slot != -1 && *clicked_gem != NULL) {
        if (slot == 0 || slot == 1) {
            if (game->inventory.fusion[slot] != NULL)
                inventory_add_gemstone(&game->inventory,
                                       *game->inventory.fusion[slot]);
            game->inventory.fusion[slot] = Gemstone_copy_ptr(*clicked_gem);
            if (game->inventory.fusion[0] != NULL &&
                game->inventory.fusion[1] != NULL) {
                Gem* gem = Gemstone_copy_ptr(game->inventory.fusion[0]);
                if (!Gemstone_merge(gem, game->inventory.fusion[1])) {
                    free(gem);
                } else {
                    game->inventory.fusion[2] = gem;
                }
            }
            *clicked_gem = NULL;
            *is_dragging = false;
            return true;
        }
    }
    return false;
}

/* Drag and drop a gemstone from the inventory, a tower or a fusion slot */
bool drag_and_drop_gemstone(Game* game, Event event, Gem** clicked_gem,
                            Point* new_gem_pos) {
    static bool is_dragging = false;
    static Tower* clicked_tower = NULL;
    if (!is_dragging &&
        (drag_gemstone_from_inventory(game, event, clicked_gem) ||
         drag_gemstone_from_tower(game, event, clicked_gem, &clicked_tower) ||
         drag_gemstone_from_fusion(game, event, clicked_gem))) {
        is_dragging = true;
    }
    if (is_dragging) {
        if (drop_gemstone_on_tower(game, event, clicked_gem, &is_dragging) ||
            drop_gemstone_on_fusion_slot(game, event, clicked_gem,
                                         &is_dragging)) {
            free(*clicked_gem);
            *clicked_gem = NULL;
            return false;
        }
        if (drop_item(event, is_dragging)) {
            inventory_add_gemstone(&game->inventory, **clicked_gem);
            free(*clicked_gem);
            *clicked_gem = NULL;
            is_dragging = false;
            return false;
        }
        if (event.type == MOUSE_BUTTON || event.type == MOUSE_MOTION) {
            new_gem_pos->x = event.mouse.x;
            new_gem_pos->y = event.mouse.y;
        }
        return true;
    }
    return false;
}
