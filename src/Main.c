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
#include "Font.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "GraphicOverlay.h"
#include "Inventory.h"
#include "Map.h"
#include "Mob.h"
#include "Path.h"
#include "Test.h"
#include "Wave.h"
#include "Window.h"
#include "tools/TimeManager.h"

// int main(int argc, char const* argv[]) {
//     DynamicArray da;
//     DA_init(&da, 10, PATH);
//     Coord_i coord1 = {.x = 1, .y = 2};
//     Coord_i coord2 = {.x = 1, .y = 3};
//     Coord_i coord3 = {.x = 1, .y = 4};
//     DA_add(&da, (DynamicArray_Union){.path = coord1}, PATH);
//     DA_add(&da, (DynamicArray_Union){.path = coord2}, PATH);
//     DA_add(&da, (DynamicArray_Union){.path = coord3}, PATH);
//     DA_print_all(&da);
//     return 0;
// }

int main(int argc, char const *argv[]) {
    // struct timespec origin_time, new_time;
    // clock_gettime(CLOCK_MONOTONIC, &origin_time);

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
        printf("retry\n");
    }

    Map_print(&map);
    DA_print_all(&da);

    Error err = Wave_init(&(map.mobs));
    if (err) {
        Error_print(err, "Wave_Init");
        DA_free(da);
        return EXIT_FAILURE;
    }
    // Wave_spawn_next(&(map.mobs), Utils_coord_i_to_f_center(map.nest));
    // fprintf(stderr, "next wave %ld\n", map.mobs.next_mob.tv_sec);
    // Mob_init_basic(1, Utils_coord_i_to_f_center(map.nest));
    printf("finish\n");
    // clock_gettime(CLOCK_MONOTONIC, &new_time);
    // printf("time %ld\n", Time_ms_interval(origin_time, new_time));
    // printf("time s %ld\n", new_time.tv_sec - origin_time.tv_sec);
    // printf("time ns %ld\n", new_time.tv_nsec - origin_time.tv_nsec);
    // return 0;
    // Test_graphic_field(map, &window);
    SubWindow map_window = SubWindow_init(&window, (Coord_f){0, 0}, 1120, 880);
    SubWindow inventory_window =
        SubWindow_init(&window, (Coord_f){1120, 0}, 280, 880);
    MLV_create_window("Test", "Test", window.width, window.height);
    inventory_window.font =
        font_load("assets/fonts/unifont.ttf", inventory_window.width / 7);
    int acc = 0;
    MLV_change_frame_rate(60);
    Wave_next_step(&map.mobs, &da);
    // Direction mob_dir =
    //     Map_got_next_path(&map, Utils_coord_f_to_i(map.mobs.pos), NO_DIR);
    int page = 0;
    while (1) {
        if (acc == 0) {
            draw_map(map, map_window, &da);
            show_mana_bar(inventory.mana, 180, 810, 760, 20, 3);
            MLV_draw_text(180 + 760 / 2, 810, "%d/%d", MLV_COLOR_BLACK,
                          inventory.mana.mana_real, inventory.mana.mana_max);
            draw_inventory(inventory_window, inventory);
            clear_gems_and_pagination_area(inventory_window);
            if (page > 2) {
                page = 0;
            }
            draw_gems_and_pagination(inventory_window, inventory, page++);
        }
        clear_path_cells(map.board, map_window);
        draw_path_cells(map.board, map_window, NULL);
        draw_mobs(&(map.mobs), map_window, NULL);
        draw_turn(&da, map_window);
        refresh_window();
        // mob_dir = Map_got_next_path(&map, Utils_coord_f_to_i(map.mobs.pos),
        //                             (mob_dir + 2) % 4);
        // printf("dir %d, ingnore %d\n", mob_dir, (mob_dir + 2) % 4);
        Wave_next_step(&map.mobs, &da);
        Wave_spawn_next(&(map.mobs), Utils_coord_i_to_f_center(map.nest));

        acc++;

        MLV_delay_according_to_frame_rate();
    }
    return 0;
}
