/**
 * @file GraphicField.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "GraphicField.h"

#include "Graphic.h"

/**
 * @brief Draw the given tower on the given window.
 * If img is NULL, draw a circle with tower color instead.
 *
 * @param tower Tower to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 */
static void draw_tower(Tower tower, SubWindow window, MLV_Image* img) {
    if (img) {
        MLV_draw_image(img, tower.coord.x * window.width / MAP_WIDTH,
                       tower.coord.y * window.height / MAP_HEIGHT);
    } else {
        MLV_Color color = MLV_COLOR_BLACK;
        if (tower.gem) {
            color = RGB_to_MLV_Color(HSV_to_RGB(tower.gem->color), 255);
        }
        MLV_draw_filled_circle(tower.coord.x * window.width / MAP_WIDTH,
                               tower.coord.y * window.height / MAP_HEIGHT,
                               window.width / MAP_WIDTH / 2, color);
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
static bool draw_path_cell(Cell cell, SubWindow window, MLV_Image* img) {
    MLV_Color color = MLV_COLOR_LIGHT_GREY;
    int cell_width = window.width / MAP_WIDTH;
    int cell_height = window.height / MAP_HEIGHT;
    if (cell.is_path) {
        if (img)
            MLV_draw_image(img, cell.coord.x * cell_width,
                           cell.coord.y * cell_height);
        else
            MLV_draw_filled_rectangle(cell.coord.x * cell_width,
                                      cell.coord.y * cell_height, cell_width,
                                      cell_height, color);
        return true;
    }
    return false;
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
    MLV_clear_window(MLV_COLOR_WHITE);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            draw_path_cell(map.board[i][j], map_window, NULL);
            if (map.board[i][j].tower) {
                draw_tower(*map.board[i][j].tower, map_window, NULL);
            }
        }
    }
    draw_grid(map_window, MLV_COLOR_BLACK, 2);
    MLV_actualise_window();
}