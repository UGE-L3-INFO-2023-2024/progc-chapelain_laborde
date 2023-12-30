/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DynamicArray.h"
#include "Event.h"
#include "FieldEvent.h"
#include "Font.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "GraphicOverlay.h"
#include "Inventory.h"
#include "InventoryEvent.h"
#include "Mana.h"
#include "Map.h"
#include "Mob.h"
#include "Path.h"
#include "Test.h"
#include "TimeManager.h"
#include "Wave.h"
#include "Window.h"

static void tower_button_action(ButtonTab buttons, SubWindow inventory_window,
                                SubWindow map_window, Map* map, Event event) {
    Button* tower_button = button_tab_get_button(buttons, "tower");
    if (tower_button != NULL) {
        if (click_on_button(inventory_window, event, *tower_button) &&
            event.mouse.state == MLV_PRESSED) {
            tower_button->pressed = !tower_button->pressed;
        }
        if (tower_button->pressed && event.type == MOUSE_BUTTON &&
            event.mouse.state == MLV_PRESSED) {
            Coord_i coord = get_coord_on_map(
                *map, map_window, (Coord_i){event.mouse.x, event.mouse.y});
            if (coord.x >= 0 && coord.x < MAP_WIDTH && coord.y >= 0 &&
                coord.y < MAP_HEIGHT) {
                if (!map->board[coord.y][coord.x].is_path &&
                    !map->board[coord.y][coord.x].have_tower) {
                    Tower tower = Tower_init(coord);
                    // if (Mana_buy(&inventory.mana,
                    //              Mana_tower_cost(map.towers.real_len)))
                    Map_add_tower(map, tower);
                }
            }
        }
    }
}

static void auto_release_button(Button* button, Event event) {
    if (event.type == MOUSE_BUTTON && event.mouse.state == MLV_RELEASED) {
        button->pressed = false;
    }
}

static void mana_button_action(ButtonTab buttons, SubWindow inventory_window,
                               ManaPool* pool, Event event) {
    Button* mana_button = button_tab_get_button(buttons, "mana");
    if (mana_button != NULL) {
        if (click_on_button(inventory_window, event, *mana_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                mana_button->pressed = true;
                Mana_pool_upgrade(pool);  // TODO: add alert if not enough mana
            }
        }
        auto_release_button(mana_button, event);
    }
}

static void gem_minus_button_action(ButtonTab buttons,
                                    SubWindow inventory_window,
                                    Inventory* inventory, Event event,
                                    int* gem_level) {
    Button* minus_button = button_tab_get_button(buttons, "minus");
    if (minus_button != NULL) {
        if (click_on_button(inventory_window, event, *minus_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                if (*gem_level > 1) {
                    minus_button->pressed = true;
                    (*gem_level)--;
                }
            }
        }
        auto_release_button(minus_button, event);
    }
}

static void gem_plus_button_action(ButtonTab buttons,
                                   SubWindow inventory_window,
                                   Inventory* inventory, Event event,
                                   int* gem_level) {
    Button* plus_button = button_tab_get_button(buttons, "plus");
    if (plus_button != NULL) {
        if (click_on_button(inventory_window, event, *plus_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                plus_button->pressed = true;
                (*gem_level)++;
            }
        }
        auto_release_button(plus_button, event);
    }
}

static void gem_button_action(ButtonTab buttons, SubWindow inventory_window,
                              Inventory* inventory, Event event) {
    Button* gem_button = button_tab_get_button(buttons, "gem");
    if (gem_button != NULL) {
        if (click_on_button(inventory_window, event, *gem_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                gem_button->pressed = true;
                inventory_add_gemstone(
                    inventory, Gemstone_init());  // TODO: add level parameter
                                                  // to gemstone_init
                // TODO: add alert if not enough mana
            }
        }
        auto_release_button(gem_button, event);
    }
}

static void gem_buttons_action(ButtonTab buttons, SubWindow inventory_window,
                               Inventory* inventory, Event event,
                               int* gem_level) {
    gem_minus_button_action(buttons, inventory_window, inventory, event,
                            gem_level);
    gem_plus_button_action(buttons, inventory_window, inventory, event,
                           gem_level);
    gem_button_action(buttons, inventory_window, inventory, event);
}

static void inventory_button_action(ButtonTab buttons,
                                    SubWindow inventory_window, Event event,
                                    int* page, int max_page) {
    Button* left_button = button_tab_get_button(buttons, "left");
    Button* right_button = button_tab_get_button(buttons, "right");
    if (left_button != NULL) {
        if (click_on_button(inventory_window, event, *left_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                if (*page > 0) {
                    left_button->pressed = true;
                    (*page)--;
                }
            }
        }
        auto_release_button(left_button, event);
    }
    if (right_button != NULL) {
        if (click_on_button(inventory_window, event, *right_button)) {
            if (event.mouse.state == MLV_PRESSED) {
                if (*page < max_page) {
                    right_button->pressed = true;
                    (*page)++;
                }
            }
        }
        auto_release_button(right_button, event);
    }
}

int main(int argc, char const* argv[]) {
    Window window = Window_init((Coord_f){0, 0}, 1400, 880);
    srand(time(NULL));
    DynamicArray da;
    if (DA_init(&da, 10, PATH)) {
        exit(EXIT_FAILURE);
    }
    Inventory inventory;
    inventory_init(&inventory);
    for (int i = 0; i < 35; i++)
        inventory_add_gemstone(&inventory, Gemstone_init());
    Map map = Map_init();
    while (!Path_gen(&map, &da)) {
        da.real_len = 0;
    }

    Error err = Map_init_towers(&map);
    if (err) {
        Error_print(err, "Map_init_towers");
        DA_free(da);
        return EXIT_FAILURE;
    }

    err = Wave_init(&(map.mobs));
    if (err) {
        Error_print(err, "Wave_Init");
        DA_free(da);
        DA_free(map.towers);
        return EXIT_FAILURE;
    }

    SubWindow map_window = SubWindow_init(&window, (Coord_f){0, 0}, 1120, 880);
    SubWindow inventory_window =
        SubWindow_init(&window, (Coord_f){1120, 0}, 280, 880);
    MLV_create_window("Test", "Test", window.width, window.height);
    inventory_window.font =
        font_load("assets/fonts/unifont.ttf", inventory_window.width / 7);
    MLV_change_frame_rate(60);
    Wave_next_step(&map.mobs, &da);

    int inventory_gem_level = 1;
    int inventory_page = 0;

    ButtonTab buttons;
    button_tab_init(&buttons);
    create_inventory_buttons(inventory_window, &buttons);
    Event event;
    while (1) {
        event = get_event();
        if (quit_event(event)) {
            break;
        }
        tower_button_action(buttons, inventory_window, map_window, &map,
                            event);
        mana_button_action(buttons, inventory_window, &(inventory.mana),
                           event);
        gem_buttons_action(buttons, inventory_window, &inventory, event,
                           &inventory_gem_level);
        inventory_button_action(buttons, inventory_window, event,
                                &inventory_page,
                                inventory.gemstones_count / GEMS_PER_PAGE);
        draw_map(map, map_window, &da);
        show_mana_bar(inventory.mana, 180, 810, 760, 40, 3);
        draw_inventory_menu(inventory_window, inventory, buttons,
                            inventory_gem_level, inventory_page);
        draw_mobs(&(map.mobs), map_window, NULL);
        refresh_window();
        Wave_next_step(&map.mobs, &da);
        Wave_spawn_next(&(map.mobs), Utils_coord_i_to_f_center(map.nest));

        MLV_delay_according_to_frame_rate();
    }
    return 0;
}
