/**
 * @file ButtonAction.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Gestor of button action
 * @date 07-01-2024
 *
 */

#include "ButtonAction.h"

#include <stdarg.h>

#include "Button.h"
#include "Event.h"
#include "FieldEvent.h"
#include "Game.h"
#include "Inventory.h"
#include "InventoryEvent.h"
#include "Mana.h"
#include "Map.h"
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
static Button* get_clicked_button(ButtonTab buttons, SubWindow window,
                                  Event event) {
    Button* pressed_button = get_button_actually_pressed(buttons);
    for (int i = 0; i < buttons.count; i++) {
        Button* button = buttons.buttons[i];
        if (button != NULL && click_on_button(window, event, *button) &&
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

static void tower_button_action(Button* button, SubWindow map_window, Map* map,
                                ManaPool* mana_pool, Event event) {
    Coord_i coord = get_coord_on_map(*map, map_window,
                                     (Coord_i){event.mouse.x, event.mouse.y});
    if (coord.x >= 0 && coord.x < MAP_WIDTH && coord.y >= 0 &&
        coord.y < MAP_HEIGHT) {
        if (!map->board[coord.y][coord.x].is_path &&
            !map->board[coord.y][coord.x].have_tower) {
            Tower tower = Tower_init(coord);
            // TODO 300 : add alert if not enough mana
            if (Mana_buy(mana_pool, Mana_tower_cost(map->towers.real_len)))
                Map_add_tower(map, tower);
            button->pressed = false;
        }
    }
}

static void mana_button_action(ManaPool* pool) {
    if (!Mana_pool_upgrade(pool)) {
        // TODO 300 : add alert if not enough mana
    }
}

static void gem_minus_button_action(int* gem_level) {
    if (*gem_level > 0)
        (*gem_level)--;
}

static void gem_plus_button_action(int* gem_level) {
    if (*gem_level < 10)
        (*gem_level)++;
}

static void gem_button_action(Inventory* inventory, ManaPool* mana_pool,
                              int gem_level) {
    if (Mana_buy(mana_pool, Mana_gem_cost(gem_level)))
        inventory_add_gemstone(inventory, Gemstone_init(gem_level));
}

static void left_page_inventory_button_action(int* page) {
    if (*page > 0) {
        (*page)--;
    }
}

static void right_page_inventory_button_action(int* page, int max_page) {
    if (*page < max_page) {
        (*page)++;
    }
}

void doing_button_actions(ButtonTab buttons, SubWindow inventory_window,
                          SubWindow map_window, Game* game, Event event) {
    get_clicked_button(buttons, inventory_window, event);
    Button* button = get_button_actually_pressed(buttons);
    if (button == NULL || !button->pressed || button->name == NULL) {
        return;
    }
    if (event.mouse.state == MLV_RELEASED) {
        if (strcmp(button->name, "tower") == 0) {
            tower_button_action(button, map_window, &game->map,
                                &game->mana_pool, event);
        } else {
            if (strcmp(button->name, "mana") == 0) {
                mana_button_action(&game->mana_pool);
            } else if (strcmp(button->name, "minus") == 0) {
                gem_minus_button_action(&game->inventory.info.gem_level);
            } else if (strcmp(button->name, "plus") == 0) {
                gem_plus_button_action(&game->inventory.info.gem_level);
            } else if (strcmp(button->name, "gem") == 0) {
                gem_button_action(&game->inventory, &game->mana_pool,
                                  game->inventory.info.gem_level);
            } else if (strcmp(button->name, "left") == 0) {
                left_page_inventory_button_action(&game->inventory.info.page);
            } else if (strcmp(button->name, "right") == 0) {
                right_page_inventory_button_action(
                    &game->inventory.info.page,
                    (game->inventory.gemstones_count - 1) / GEMS_PER_PAGE);
            } else {
                fprintf(stderr, "Error : button name not found\n");
            }
            button->pressed = false;
        }
    }
}
