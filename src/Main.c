/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 07-01-2024
 *
 */
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ButtonAction.h"
#include "DynamicArray.h"
#include "Error.h"
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

int main(int argc, char const* argv[]) {
    Window window = Window_init((Coord_f){0, 0}, 1400, 880);
    srand(time(NULL));
    DynamicArray da;
    if (DA_init(&da, 10, PATH).type) {
        exit(EXIT_FAILURE);
    }
    Inventory inventory;
    inventory_init(&inventory);
    for (int i = 0; i < 35; i++)
        inventory_add_gemstone(&inventory, Gemstone_init(1));
    Map map = Map_init();
    while (!Path_gen(&map, &da)) {
        da.real_len = 0;
    }

    Error err = Map_init_towers(&map);
    if (err.type) {
        Error_print(err);
        DA_free(da);
        return EXIT_FAILURE;
    }

    err = Wave_init(&(map.mobs));
    if (err.type) {
        Error_print(err);
        DA_free(da);
        DA_free(map.towers);
        return EXIT_FAILURE;
    }

    err = Map_init_projs(&map);
    if (err.type) {
        Error_print(err);
        DA_free(da);
        DA_free(map.towers);
        DA_free(map.mobs.mob_list);
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

    int inventory_gem_level = 0;
    int inventory_page = 0;

    ButtonTab buttons;
    button_tab_init(&buttons);
    create_inventory_buttons(inventory_window, &buttons);
    Event event = {NO_EVENT};
    Tower* clicked_tower = NULL;
    Gem* clicked_gem = NULL;
    int slot = -1;
    while (!quit_event(event)) {
        event = get_event();
        doing_button_actions(buttons, inventory_window, map_window, &map,
                             &inventory, event, &inventory_gem_level,
                             &inventory_page);
        if (clicked_gem == NULL)
            clicked_gem = click_on_gemstone(inventory_window, event, inventory,
                                            inventory_page);
        slot = click_on_fusion_slot(inventory_window, event);
        if (slot != -1 && clicked_gem != NULL) {
            if (slot == 0 || slot == 1) {
                if (inventory.fusion[slot] != NULL)
                    inventory_add_gemstone(&inventory,
                                           *inventory.fusion[slot]);
                inventory.fusion[slot] = Gemstone_copy_ptr(clicked_gem);
                inventory_remove_gemstone(&inventory, *clicked_gem);
                clicked_gem = NULL;
            }
        }
        if (slot == 2 && clicked_gem == NULL) {
            if (inventory.fusion[0] != NULL && inventory.fusion[1] != NULL) {
                if (Gemstone_merge(inventory.fusion[0], inventory.fusion[1])) {
                    inventory_add_gemstone(&inventory, *inventory.fusion[0]);
                    free(inventory.fusion[0]);
                    free(inventory.fusion[1]);
                    inventory.fusion[0] = NULL;
                    inventory.fusion[1] = NULL;
                }
            }
        }
        clicked_tower = click_on_tower(map_window, event, map);
        if (clicked_tower != NULL && clicked_gem != NULL) {
            if (clicked_tower->has_gem) {
                Gem tower_gem;
                Tower_extract_gem(clicked_tower, &tower_gem);
                inventory_add_gemstone(&inventory, tower_gem);
            }
            Tower_add_gem(clicked_tower, clicked_gem);
            inventory_remove_gemstone(&inventory, *clicked_gem);
            clicked_gem = NULL;
        }
        draw_map(map, map_window, &da);
        show_mana_bar(inventory.mana, 180, 810, 760, 40, 3);
        draw_inventory_menu(inventory_window, inventory, buttons,
                            inventory_gem_level, inventory_page);
        draw_mobs(&(map.mobs), map_window, NULL);
        refresh_window();
        Wave_next_step(&map.mobs, &da);
        Map_towers_shoot(&map);
        Map_actualise_proj(&map);
        // DA_print_all(&map.mobs.mob_list);
        err =
            Wave_spawn_next(&(map.mobs), Utils_coord_i_to_f_center(map.nest));
        if (err.type) {
            Error_print(err);
            return EXIT_FAILURE;
        }

        MLV_delay_according_to_frame_rate();
    }
    return 0;
}
