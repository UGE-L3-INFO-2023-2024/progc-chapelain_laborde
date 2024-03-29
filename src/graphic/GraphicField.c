/**
 * @file GraphicField.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains functions to draw the field.
 * @date 14-11-2023
 *
 */

#include "GraphicField.h"

#include "Color.h"
#include "DynamicArray.h"
#include "Graphic.h"
#include "GraphicInventory.h"
#include "Utils.h"
#include "Wave.h"

/**
 * @brief Draw a tower in the map.
 * The img parameter is used to draw an image instead of the tower.
 * If img is NULL, draw a black tower with a colored gem in the middle.
 * The gem color is the tower gem color.
 *
 * @param tower Tower to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of the drawed tower.
 */
static void draw_tower(Tower tower, SubWindow window, const MLV_Image* img) {
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    int x = tower.coord.x * cell_width;
    int y = tower.coord.y * cell_height;
    int corner_width = (int)(cell_width * 0.25);
    int corner_height = (int)(cell_height * 0.25);
    int gem_margin_w = (int)(cell_width * 0.15);
    int gem_margin_h = (int)(cell_height * 0.15);
    if (img) {
        MLV_draw_image(img, x, y);
    } else {
        // Drawing tower
        MLV_Color color = MLV_COLOR_BLACK;
        MLV_draw_filled_rectangle(x, y, corner_width, corner_height, color);
        MLV_draw_filled_rectangle(x + cell_width - corner_width, y,
                                  corner_width, corner_height, color);
        MLV_draw_filled_rectangle(x, y + cell_height - corner_height,
                                  corner_width, corner_height, color);
        MLV_draw_filled_rectangle(x + cell_width - corner_width,
                                  y + cell_height - corner_height,
                                  corner_width, corner_height, color);
        MLV_draw_filled_rectangle(x + corner_width / 2, y + corner_height / 2,
                                  cell_width - corner_width,
                                  cell_height - corner_height, CLEAR_COLOR);
        // Drawing gem
        if (tower.has_gem) {
            draw_gem((Coord_i){x + gem_margin_w, y + gem_margin_h},
                     cell_width - 2 * gem_margin_w,
                     cell_height - 2 * gem_margin_h, tower.gem);
        }
    }
}

/**
 * @brief Draw a cell path of the map.
 *
 * @param cell Cell to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a grey rectangle.
 *
 * @return bool true if the cell is a path, false otherwise.
 */
static void draw_path(Coord_i coord, SubWindow window, const MLV_Image* img) {
    MLV_Color color = MLV_COLOR_LIGHT_GREY;
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    if (img) {
        MLV_draw_image(img, coord.x * cell_width, coord.y * cell_height);
    } else {
        MLV_draw_filled_rectangle(coord.x * cell_width, coord.y * cell_height,
                                  cell_width, cell_height, color);
        MLV_draw_rectangle(coord.x * cell_width, coord.y * cell_height,
                           cell_width, cell_height, MLV_COLOR_BLACK);
    }
}

/**
 * @brief Draw a nest of the map.
 *
 * @param cell Nest to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a red rectangle.
 *
 */
static void draw_nest(Coord_i nest, SubWindow window, const MLV_Image* img) {
    MLV_Color color = MLV_COLOR_LIGHT_SALMON;
    int nest_width = window.width / MAP_WIDTH;
    int nest_height = window.height / MAP_HEIGHT;
    if (img)
        MLV_draw_image(img, nest.x * nest_width, nest.y * nest_height);
    else
        MLV_draw_filled_rectangle(nest.x * nest_width, nest.y * nest_height,
                                  nest_width, nest_height, color);
}

/**
 * @brief Draw a castle of the map.
 *
 * @param cell Castle to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a green rectangle.
 *
 */
static void draw_castle(Coord_i castle, SubWindow window,
                        const MLV_Image* img) {
    MLV_Color color = MLV_COLOR_LIGHT_GREEN;
    int castle_width = window.width / MAP_WIDTH;
    int castle_height = window.height / MAP_HEIGHT;
    if (img)
        MLV_draw_image(img, castle.x * castle_width, castle.y * castle_height);
    else
        MLV_draw_filled_rectangle(castle.x * castle_width,
                                  castle.y * castle_height, castle_width,
                                  castle_height, color);
}

/**
 * @brief Draw a mob of the map.
 *
 * @param wave Wave to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a colored circle.
 */
void draw_mobs(Wave wave, SubWindow window, const MLV_Image* img) {
    int mob_width = window.width / MAP_WIDTH;
    int mob_height = window.height / MAP_HEIGHT;
    for (int i = 0; i < wave.mob_list.real_len; i++) {
        Mob mob = *(wave.mob_list.arr[i].mob);
        Coord_i bar_pos = {
            .x = (int)(mob.pos.x * mob_width - mob_width / 3),
            .y = (int)(mob.pos.y * mob_height + mob_height / 4)};
        MLV_Color color = RGB_to_MLV_Color(Color_HSV_to_RGB(mob.color), 255);
        if (img)
            MLV_draw_image(img, (int)(mob.pos.x * mob_width),
                           (int)(mob.pos.y * mob_height));
        else
            MLV_draw_filled_circle((int)(mob.pos.x * mob_width),
                                   (int)(mob.pos.y * mob_height),
                                   mob_width / 4, color);

        draw_bar(bar_pos, (int)(mob_width / 1.5), mob_height / 6, 1, color,
                 (float)(mob.current_hp / (double)mob.max_hp),
                 MLV_COLOR_GREEN);
    }
}

/**
 * @brief Draw a projectile of the map.
 *
 * @param wave Wave to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a colored circle.
 */
static void draw_projectile(DynamicArray projs, SubWindow window,
                            const MLV_Image* img) {
    for (int i = 0; i < projs.real_len; i++) {
        Projectile proj = (projs.arr[i].proj);
        MLV_Color color =
            RGB_to_MLV_Color(Color_HSV_to_RGB(proj.gem.color), 255);
        int proj_width = window.width / MAP_WIDTH;
        int proj_height = window.height / MAP_HEIGHT;
        if (img)
            MLV_draw_image(img, (int)(proj.pos.x * proj_width),
                           (int)(proj.pos.y * proj_height));
        else
            MLV_draw_filled_circle((int)(proj.pos.x * proj_width),
                                   (int)(proj.pos.y * proj_height),
                                   proj_width / 6, color);
    }
}

/**
 * @brief Draw the map grid according to the window size.
 *
 * @param window Window to get the size of.
 * @param color Color of the grid.
 * @param thickness Thickness of lines of the grid.
 */
static void draw_grid(SubWindow window, MLV_Color color, int thickness) {
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    draw_rectangle(0, 0, cell_width * MAP_WIDTH, cell_height * MAP_HEIGHT,
                   thickness, color);
    for (int i = 1; i < MAP_WIDTH; i++) {
        MLV_draw_filled_rectangle(i * cell_width - thickness / 2, 0, thickness,
                                  cell_height * MAP_HEIGHT, MLV_COLOR_BLACK);
    }
    for (int i = 1; i < MAP_HEIGHT; i++) {
        MLV_draw_filled_rectangle(0, i * cell_height - thickness / 2,
                                  cell_width * MAP_WIDTH, thickness,
                                  MLV_COLOR_BLACK);
    }
}

/* Draw map in the window */
void draw_map(Map map, SubWindow map_window) {
    MLV_clear_window(CLEAR_COLOR);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map.board[i][j].is_path)
                draw_path((Coord_i){j, i}, map_window, NULL);
            if (map.board[i][j].have_tower) {
                Tower tower = *Map_get_tower(&map, (Coord_i){j, i});
                draw_tower(tower, map_window, NULL);
            }
        }
    }
    draw_castle(map.castle, map_window, NULL);
    draw_nest(map.nest, map_window, NULL);
    draw_projectile(map.projs, map_window, NULL);
    draw_grid(map_window, MLV_COLOR_BLACK, 2);
}