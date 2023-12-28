#include "GraphicInventory.h"

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Gemstone.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "Inventory.h"
#include "Window.h"

#define GEMS_PER_PAGE 12

void draw_gem(Coord_i coord, int w, int h, RGB_Color color) {
    MLV_Color mlv_color = RGB_to_MLV_Color(color, 255);
    MLV_draw_filled_rectangle(coord.x, coord.y, w, h, mlv_color);
    MLV_draw_rectangle(coord.x, coord.y, w, h, MLV_COLOR_BLACK);
}

/**
 * @brief Draw all the gems of the inventory on the screen.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory containing the gems to draw.
 * @param page The page of the inventory gems to draw.
 * @param actual_pourcent The actual pourcent of the window used in y axis.
 * Page start at 0 not 1.
 */
static void draw_all_gems(SubWindow window, Inventory inventory,
                          unsigned int page) {
    double actual_pourcent = 0.25;
    Coord_i coord;
    int gemSize = window.width * 0.6 / 3;
    int gemSpace = window.width * 0.4 / 4;

    for (int i = page * GEMS_PER_PAGE, j = 0;
         i < inventory.gemstones_count &&
         i < GEMS_PER_PAGE + (page * GEMS_PER_PAGE);
         i++, j++) {
        if (j % 3 == 0 && j != 0) {
            actual_pourcent += 0.1;
            j = 0;
        }
        RGB_Color rgb_color_gem =
            Color_HSV_to_RGB(inventory.gemstones[i].color);
        coord = (Coord_i){window.coord.x + gemSpace * (j + 1) + gemSize * j,
                          window.coord.y + window.height * actual_pourcent};
        draw_gem(coord, gemSize, gemSize, rgb_color_gem);
    }
}

static void draw_pagination(Coord_i coord, int w, int h, Font font,
                            unsigned int page, unsigned int max_page) {
    double actual_pourcent = 0.65;
    MLV_Color left_chevron = MLV_COLOR_BLACK;
    MLV_Color right_chevron = MLV_COLOR_BLACK;
    if (page == 1) {
        left_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    if (max_page == page) {
        right_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    draw_centered_text(coord.x + w * 0.2, coord.y + h * actual_pourcent, "<",
                       font, left_chevron);
    draw_centered_text(coord.x + w / 2, coord.y + h * actual_pourcent, "%d/%d",
                       font, MLV_COLOR_BLACK, page, max_page);
    draw_centered_text(coord.x + w * 0.8, coord.y + h * actual_pourcent, ">",
                       font, right_chevron);
}

void draw_gems_and_pagination(SubWindow window, Inventory inventory,
                              unsigned int page) {
    draw_all_gems(window, inventory, page);
    draw_pagination((Coord_i){window.coord.x, window.coord.y}, window.width,
                    window.height, window.font, page + 1,
                    inventory.gemstones_count / 15 + 1);
}

void clear_gems_and_pagination_area(SubWindow window) {
    window.coord.y += window.height * 0.25;
    window.height *= (0.65 - 0.21);
    clear_window(window);
}

void draw_inventory(SubWindow window, Inventory inventory) {
    int page = 0;
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    double actual_pourcent = 0.025;
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Tower Defense",
                       window.font, MLV_COLOR_BLACK);
    actual_pourcent += 0.04;
    draw_line(x, y + h * actual_pourcent, x + w, y + h * actual_pourcent, 2,
              MLV_COLOR_BLACK);
    draw_tower(window, NULL, x + w * 0.1, y + h * actual_pourcent - w * 0.2,
               w * 0.2, h * 0.2);

    actual_pourcent += 0.09;
    draw_line(x, y + h * actual_pourcent, x + w, y + h * actual_pourcent, 2,
              MLV_COLOR_BLACK);

    actual_pourcent += 0.03;
    // 5% for the title
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Inventory",
                       window.font, MLV_COLOR_BLACK);
    actual_pourcent += 0.04;

    draw_line(x, y + h * actual_pourcent, x + w, y + h * actual_pourcent, 2,
              MLV_COLOR_BLACK);

    // 10% for the space between gems
    draw_gems_and_pagination(window, inventory, page);
    actual_pourcent = 0.7;

    draw_line(x, y + h * actual_pourcent, x + w, y + h * actual_pourcent, 2,
              MLV_COLOR_BLACK);

    actual_pourcent += 0.03;

    // 1% for the space between the title and the gems
    actual_pourcent += 0.01;
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Fusion",
                       window.font, MLV_COLOR_BLACK);

    // 5% for the fusion title
    actual_pourcent += 0.05;

    draw_line(x, y + h * actual_pourcent, x + w, y + h * actual_pourcent, 2,
              MLV_COLOR_BLACK);

    actual_pourcent += 0.025;
    // 1% for the space between the title and the gems
    // 10% for the two gems to fusion
    Coord_i coord = (Coord_i){x + w * 0.05, y + h * actual_pourcent};
    draw_gem(coord, w * 0.2, w * 0.2, (RGB_Color){211, 211, 211});
    draw_centered_text(x + w * 0.325, y + h * (actual_pourcent + 0.025), "+",
                       window.font, MLV_COLOR_BLACK);
    coord.x = x + w * 0.4;
    draw_gem(coord, w * 0.2, w * 0.2, (RGB_Color){211, 211, 211});
    draw_centered_text(x + w * 0.675, y + h * (actual_pourcent + 0.025), "=",
                       window.font, MLV_COLOR_BLACK);
    coord.x = x + w * 0.75;
    draw_gem(coord, w * 0.2, w * 0.2, (RGB_Color){211, 211, 211});
    // 1% for the space between the title and the gems
    // 5% for the button
    actual_pourcent += 0.125;
    MLV_draw_filled_rectangle(x + w * 0.1, y + h * (actual_pourcent - 0.025),
                              w * 0.8, h * 0.05, MLV_COLOR_LIGHT_GRAY);
    // TODO : add check image and cancel image for fusion
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Fusion",
                       window.font, MLV_COLOR_BLACK);
    // 1% for the space between the title and the gems
}
