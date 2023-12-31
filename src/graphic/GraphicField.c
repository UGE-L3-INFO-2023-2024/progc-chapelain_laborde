/**
 * @file GraphicField.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "GraphicField.h"

#include "Color.h"
#include "DynamicArray.h"
#include "Graphic.h"
#include "Wave.h"

void draw_tower(SubWindow window, MLV_Image* img, int x, int y, int width,
                int height) {
    if (img) {
        MLV_resize_image(img, width, height);
        MLV_draw_image(img, x, y);
    } else {
        MLV_Color color = MLV_COLOR_BLACK;
        MLV_draw_filled_circle(x + width / 2, y + height / 2, width / 2,
                               color);
    }
}

static void draw_tower_in_map(Tower tower, SubWindow window, MLV_Image* img) {
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    if (img) {
        MLV_draw_image(img, tower.coord.x * cell_width,
                       tower.coord.y * cell_height);
    } else {
        MLV_Color color = MLV_COLOR_BLACK;
        if (tower.gem) {
            color = RGB_to_MLV_Color(Color_HSV_to_RGB(tower.gem->color), 255);
        }
        MLV_draw_filled_circle(tower.coord.x * cell_width + cell_width / 2,
                               tower.coord.y * cell_height + cell_height / 2,
                               (cell_width / 2) * 0.9, color);
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
static void draw_path(Coord_i coord, SubWindow window, MLV_Image* img) {
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

void draw_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window,
                     MLV_Image* img) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (cells[i][j].is_path)
                draw_path((Coord_i){j, i}, window, NULL);
        }
    }
}

static void clear_path_cell(Coord_i coord, SubWindow window) {
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    MLV_draw_filled_rectangle(coord.x * cell_width, coord.y * cell_height,
                              cell_width, cell_height, CLEAR_COLOR);
}

void clear_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (cells[i][j].is_path)
                clear_path_cell((Coord_i){j, i}, window);
        }
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
static void draw_nest(Coord_i nest, SubWindow window, MLV_Image* img) {
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
static void draw_castle(Coord_i castle, SubWindow window, MLV_Image* img) {
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

void draw_turn(DynamicArray* da, SubWindow window) {
    if (da->type != PATH) {
        fprintf(stderr, "Error in draw_turn: da is not a PATH\n");
        return;
    }

    MLV_Color color = MLV_COLOR_LIGHT_SALMON;
    int turn_width = window.width / MAP_WIDTH;
    int turn_height = window.height / MAP_HEIGHT;
    for (int i = 0; i < da->real_len; i++) {
        Coord_i turn = da->arr[i].path;
        MLV_draw_filled_rectangle(turn.x * turn_width, turn.y * turn_height,
                                  turn_width, turn_height, color);
    }
}

/**
 * @brief Draw a mob of the map.
 *
 * @param wave Wave to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a colored circle.
 */
void draw_mobs(Wave* wave, SubWindow window, MLV_Image* img) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        Mob mob = *(wave->mob_list.arr[i].mob);
        MLV_Color color = RGB_to_MLV_Color(Color_HSV_to_RGB(mob.color), 255);
        int mob_width = window.width / MAP_WIDTH;
        int mob_height = window.height / MAP_HEIGHT;
        if (img)
            MLV_draw_image(img, mob.pos.x * mob_width, mob.pos.y * mob_height);
        else
            MLV_draw_filled_circle(mob.pos.x * mob_width,
                                   mob.pos.y * mob_height, mob_width / 4,
                                   color);
        draw_bar(mob.pos.x * mob_width - mob_width / 3,
                 mob.pos.y * mob_height + mob_height / 4, mob_width / 1.5,
                 mob_height / 6, 1, color, mob.current_hp / mob.max_hp,
                 MLV_COLOR_GREEN);
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
void draw_map(Map map, SubWindow map_window, DynamicArray* da) {
    MLV_clear_window(CLEAR_COLOR);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map.board[i][j].is_path)
                draw_path((Coord_i){j, i}, map_window, NULL);
            if (map.board[i][j].have_tower) {
                Tower tower = *Map_get_tower(&map, (Coord_i){j, i});
                draw_tower_in_map(tower, map_window, NULL);
            }
        }
    }
    draw_castle(map.castle, map_window, NULL);
    draw_nest(map.nest, map_window, NULL);
    // draw_turn(da, map_window, NULL);
    draw_grid(map_window, MLV_COLOR_BLACK, 2);
}