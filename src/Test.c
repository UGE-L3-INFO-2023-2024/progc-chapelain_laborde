/**
 * @file Test.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Test.h"

#include "Map.h"
#include "Window.h"

/* Test the graphic field */
void Test_graphic_field(Map map, Window* window) {
    SubWindow map_window = SubWindow_init(window, (Coord_f){0, 0}, 1120, 880);
    MLV_create_window("Test", "Test", window->width, window->height);
    draw_map(map, map_window, NULL);
}