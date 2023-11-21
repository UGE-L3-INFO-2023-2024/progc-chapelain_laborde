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

#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicOverlay.h"
#include "Map.h"
#include "Mob.h"
#include "Path.h"
#include "Test.h"
#include "Window.h"

int main(int argc, char const *argv[]) {
    Window window = Window_init((Coord_f){0, 0}, 1400, 880);
    srand(time(NULL));
    Map map = Map_init();
    while (!Path_gen(&map)) {
        // Map_print(&map);
        printf("retry\n");
    }

    Map_print(&map);
    Mob_init_basic(1, Utils_coord_i_to_f_center(map.nest));
    printf("finish\n");
    map.mobs = Mob_init_basic(1, Utils_coord_i_to_f_center(map.nest));
    // Test_graphic_field(map, &window);
    SubWindow map_window = SubWindow_init(&window, (Coord_f){0, 0}, 1120, 880);
    MLV_create_window("Test", "Test", window.width, window.height);
    struct timespec origin_time, new_time;
    clock_gettime(CLOCK_REALTIME, &origin_time);
    int acc = 0;
    MLV_change_frame_rate(60);
    Direction mob_dir =
        Map_got_next_path(&map, Utils_coord_f_to_i(map.mobs.pos), NO_DIR);
    while (1) {
        if (acc == 0) {
            draw_map(map, map_window);
            show_mana_bar(map.mana, 180, 810, 760, 20, 3);
            MLV_draw_text(180 + 760 / 2, 810, "%d/%d", MLV_COLOR_BLACK,
                          map.mana.mana_real, map.mana.mana_max);
        }
        clear_path_cells(map.board, map_window);
        draw_path_cells(map.board, map_window, NULL);
        draw_mob(map.mobs, map_window, NULL);
        refresh_window();
        mob_dir = Map_got_next_path(&map, Utils_coord_f_to_i(map.mobs.pos),
                                    (mob_dir + 2) % 4);
        printf("dir %d, ingnore %d\n", mob_dir, (mob_dir + 2) % 4);
        Mob_next_step(&map.mobs, mob_dir);
        acc++;
        clock_gettime(CLOCK_REALTIME, &new_time);

        if (new_time.tv_sec != origin_time.tv_sec) {
            clock_gettime(CLOCK_REALTIME, &origin_time);
            clock_gettime(CLOCK_REALTIME, &new_time);
            printf("acc %d\n", acc);
            acc = 0;
        }

        MLV_delay_according_to_frame_rate();
    }
    return 0;
}
