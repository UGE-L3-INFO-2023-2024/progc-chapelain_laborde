#include "GraphicInventory.h"

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Gemstone.h"
#include "Graphic.h"
#include "Inventory.h"
#include "Window.h"

#define GEMS_PER_PAGE 15

void draw_gem(Coord_i coord, int w, int h, RGB_Color color) {
    MLV_Color mlv_color = RGB_to_MLV_Color(color, 255);
    MLV_draw_filled_rectangle(coord.x, coord.y, w, h, mlv_color);
    MLV_draw_rectangle(coord.x, coord.y, w, h, MLV_COLOR_BLACK);
}

void draw_all_gems(SubWindow window, Inventory inventory,
                   double* actual_pourcent, unsigned int page) {
    Coord_i coord;
    int gemSize = window.width * 0.6 / 3;
    int gemSpace = window.width * 0.4 / 4;

    for (int i = page * GEMS_PER_PAGE, j = 0;
         i < inventory.gemstones_count &&
         i < GEMS_PER_PAGE + (page * GEMS_PER_PAGE);
         i++, j++) {
        if (j % 3 == 0 && j != 0) {
            *actual_pourcent += 0.1;
            j = 0;
        }
        RGB_Color rgb_color_gem =
            Color_HSV_to_RGB(inventory.gemstones[i].color);
        coord = (Coord_i){window.coord.x + gemSpace * (j + 1) + gemSize * j,
                          window.coord.y + window.height * (*actual_pourcent)};
        draw_gem(coord, gemSize, gemSize, rgb_color_gem);
    }
}

void draw_pagination(Coord_i coord, int w, int h, double* actual_pourcent,
                     Font font, unsigned int page, unsigned int max_page) {
    *actual_pourcent = 0.635;
    MLV_Color left_chevron = MLV_COLOR_BLACK;
    MLV_Color right_chevron = MLV_COLOR_BLACK;
    if (page == 1) {
        left_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    if (max_page == page) {
        right_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    draw_centered_text(coord.x + w * 0.2, coord.y + h * *actual_pourcent, "<",
                       font, left_chevron);
    draw_centered_text(coord.x + w / 2, coord.y + h * *actual_pourcent,
                       "%d/%d", font, MLV_COLOR_BLACK, page, max_page);
    draw_centered_text(coord.x + w * 0.8, coord.y + h * *actual_pourcent, ">",
                       font, right_chevron);
}

void draw_inventory(SubWindow window, Inventory inventory) {
    int page = 2;
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    double actual_pourcent = 0.025;
    // 5% for the title
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Inventory",
                       window.font, MLV_COLOR_BLACK);
    actual_pourcent += 0.025;

    // 6% for the space between the title and the gems
    actual_pourcent += 0.06;

    // 10% for the space between gems
    draw_all_gems(window, inventory, &actual_pourcent, page);

    // 20% for the pagination
    draw_pagination((Coord_i){x, y}, w, h, &actual_pourcent, window.font,
                    page + 1, inventory.gemstones_count / 15 + 1);
    actual_pourcent += 0.075;

    // 1% for the space between the title and the gems
    actual_pourcent += 0.01;
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Fusion",
                       window.font, MLV_COLOR_BLACK);

    // 5% for the fusion title
    actual_pourcent += 0.05;
    // 1% for the space between the title and the gems
    // 10% for the two gems to fusion
    Coord_i coord = (Coord_i){x + w * 0.1, y + h * actual_pourcent};
    draw_gem(coord, w * 0.2, w * 0.2, (RGB_Color){211, 211, 211});
    draw_centered_text(x + w * 0.5, y + h * (actual_pourcent + 0.025), "+",
                       window.font, MLV_COLOR_BLACK);
    coord.x = x + w * 0.7;
    draw_gem(coord, w * 0.2, w * 0.2, (RGB_Color){211, 211, 211});
    // 1% for the space between the title and the gems
    // 5% for the button
    actual_pourcent += 0.125;
    MLV_draw_filled_rectangle(x + w * 0.1, y + h * (actual_pourcent - 0.025),
                              w * 0.8, h * 0.05, MLV_COLOR_LIGHT_GRAY);
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Fusion",
                       window.font, MLV_COLOR_BLACK);
    // 1% for the space between the title and the gems
}
