/**
 * @file ButtonAction.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Do the action of the button clicked on.
 * @date 31-12-2023
 *
 */

#include "ButtonAction.h"

#include <stdarg.h>

#include "Button.h"
#include "Event.h"
#include "FieldEvent.h"
#include "Game.h"
#include "GraphicOverlay.h"
#include "Inventory.h"
#include "InventoryEvent.h"
#include "Mana.h"
#include "Map.h"
#include "TimeManager.h"
#include "Utils.h"
#include "Window.h"

/**
 * @brief Check if there is already a button pressed in the button tab.
 * If there is, it returns the button pressed, otherwise it returns NULL.
 *
 * @param buttons The button tab to check.
 * @return Button* The button clicked on
 */
static Button* get_button_actually_pressed(ButtonTab buttons) {
    for (int i = 0; i < buttons.count; i++) {
        Button* button = buttons.buttons[i];
        if (button != NULL && button->pressed) {
            return button;
        }
    }
    return NULL;
}

/**
 * @brief Check if the event is a click on a button. If it is, it returns
 * the button clicked on, otherwise it returns NULL.
 *
 * @param buttons The button tab to check.
 * @param window The subwindow where the buttons are displayed.
 * @param event The event to check.
 * @return Button* The button clicked on
 */
static Button* get_clicked_button(ButtonTab buttons, Event event) {
    Button* pressed_button = get_button_actually_pressed(buttons);
    for (int i = 0; i < buttons.count; i++) {
        Button* button = buttons.buttons[i];
        if (button != NULL && click_on_button(event, *button) &&
            event.mouse.state == MLV_PRESSED) {
            if (pressed_button != NULL && pressed_button != button) {
                pressed_button->pressed = false;
                button->pressed = true;
            } else {
                button->pressed = !button->pressed;
            }
            return button;
        }
    }
    return NULL;
}

/**
 * @brief Buy the tower and add it to the map.
 *
 * @param button The button to check.
 * @param map_window Window where the click was done.
 * @param map Map to add tower.
 * @param mana_pool ManaPool to buy.
 * @param event The event to check.
 * @return ManaError Error if there is not enough mana.
 */
static ManaError tower_button_action(Button* button, SubWindow map_window,
                                     Map* map, ManaPool* mana_pool,
                                     Event event) {
    ManaError err = {0, Time_get()};
    Coord_i coord =
        get_coord_on_map(map_window, (Coord_i){event.mouse.x, event.mouse.y});
    if (coord.x >= 0 && coord.x < MAP_WIDTH && coord.y >= 0 &&
        coord.y < MAP_HEIGHT && !map->board[coord.y][coord.x].is_path &&
        !map->board[coord.y][coord.x].have_tower) {
        Tower tower = Tower_init(coord);
        if (Mana_buy(mana_pool, Mana_tower_cost(map->towers.real_len))) {
            Map_add_tower(map, tower);
        } else {
            err = (ManaError){.cost = Mana_tower_cost(map->towers.real_len),
                              .timeout = Time_add_ms(Time_get(), 2000)};
        }
        button->pressed = false;
    }
    return err;
}

/**
 * @brief Upgrade the manapool and add warning effect
 * when there is not enough mana
 *
 * @param pool Manapool to check
 * @return ManaError Error if there is not enough mana.
 */
static ManaError mana_button_action(ManaPool* pool) {
    if (!Mana_pool_upgrade(pool)) {
        return (ManaError){.cost = Mana_pool_upgrade_cost(*pool),
                           .timeout = Time_add_ms(Time_get(), 2000)};
    }
    return (ManaError){.cost = 0, .timeout = Time_get()};
}

/**
 * @brief Increase the level of the gem pointer.
 *
 * @param gem_level Pointer to gem level.
 */
static void gem_minus_button_action(int* gem_level) {
    if (*gem_level > 0)
        (*gem_level)--;
}

/**
 * @brief Decrease the level of the gem pointer.
 *
 * @param gem_level Pointer to gem level.
 */
static void gem_plus_button_action(int* gem_level) {
    if (*gem_level < 10)
        (*gem_level)++;
}

/**
 * @brief Buy the gem at the level given
 *
 * @param inventory Inventory to store the gem
 * @param mana_pool Manapool to check is the is enough mana.
 * @param gem_level gem level.
 * @return ManaError Error if there is not enough mana.
 */
static ManaError gem_button_action(Inventory* inventory, ManaPool* mana_pool,
                                   int gem_level) {
    ManaError err = {0, Time_get()};
    int cost = Mana_gem_cost(gem_level);
    if (Mana_buy(mana_pool, cost)) {
        Inventory_add_gemstone(inventory, Gemstone_init(gem_level));
    } else {
        err = (ManaError){.cost = cost,
                          .timeout = Time_add_ms(Time_get(), 2000)};
    }
    return err;
}

/**
 * @brief Decrease the selected number of page if possible.
 *
 * @param page Pointer to selected page.
 */
static void left_page_inventory_button_action(int* page) {
    if (*page > 0) {
        (*page)--;
    }
}

/**
 * @brief Increase the selected number of page if possible.
 *
 * @param page Pointer to selected page.
 * @param max_page number max of page.
 */
static void right_page_inventory_button_action(int* page, int max_page) {
    if (*page < max_page) {
        (*page)++;
    }
}

/* Does action like buying gem,tower, change page or gme levels */
void doing_button_actions(ButtonTab buttons, SubWindow map_window, Game* game,
                          Event event) {
    get_clicked_button(buttons, event);
    Button* button = get_button_actually_pressed(buttons);
    if (button == NULL || !button->pressed || button->name == NULL) {
        return;
    }
    if (event.type == MOUSE_BUTTON && event.mouse.state == MLV_RELEASED) {
        if (strcmp(button->name, "tower") == 0) {
            game->mana_error = tower_button_action(
                button, map_window, &game->map, &game->mana_pool, event);
        } else {
            if (strcmp(button->name, "mana") == 0) {
                game->mana_error = mana_button_action(&game->mana_pool);
            } else if (strcmp(button->name, "minus") == 0) {
                gem_minus_button_action(&game->inventory.info.gem_level);
            } else if (strcmp(button->name, "plus") == 0) {
                gem_plus_button_action(&game->inventory.info.gem_level);
            } else if (strcmp(button->name, "gem") == 0) {
                game->mana_error =
                    gem_button_action(&game->inventory, &game->mana_pool,
                                      game->inventory.info.gem_level);
            } else if (strcmp(button->name, "left") == 0) {
                left_page_inventory_button_action(&game->inventory.info.page);
            } else if (strcmp(button->name, "right") == 0) {
                right_page_inventory_button_action(
                    &game->inventory.info.page,
                    ((int)game->inventory.gemstones_count - 1) /
                        GEMS_PER_PAGE);
            } else {
                fprintf(stderr, "Error : button name not found\n");
            }
            button->pressed = false;
        }
    }
}
