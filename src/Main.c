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
    if (DA_init(&da, 10, PATH)) {
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

    err = Map_init_projs(&map);
    if (err) {
        Error_print(err, "Wave_Init");
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
    Event event = {0};
    while (!quit_event(event)) {
        event = get_event();
        doing_button_actions(buttons, inventory_window, map_window, &map,
                             &inventory, event, &inventory_gem_level,
                             &inventory_page);
        draw_map(map, map_window, &da);
        show_mana_bar(inventory.mana, 180, 810, 760, 40, 3);
        draw_inventory_menu(inventory_window, inventory, buttons,
                            inventory_gem_level, inventory_page);
        draw_mobs(&(map.mobs), map_window, NULL);
        refresh_window();
        Wave_next_step(&map.mobs, &da);
        Map_towers_shoot(&map);
        Map_actualise_proj(&map);
        err =
            Wave_spawn_next(&(map.mobs), Utils_coord_i_to_f_center(map.nest));
        if (err) {
            Error_print(err, "Wave_spawn_next");
            return EXIT_FAILURE;
        }

        MLV_delay_according_to_frame_rate();
    }
    return 0;
}
