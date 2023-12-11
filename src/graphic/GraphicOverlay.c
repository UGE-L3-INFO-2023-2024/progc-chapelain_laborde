/**
 * @file GraphicOverlay.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Overlay graphic functions
 * @date 2023-11-20
 *
 */

#include "GraphicOverlay.h"

#include <MLV/MLV_all.h>

#include "Gemstone.h"
#include "Graphic.h"
#include "Inventory.h"

void show_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness) {
    int mana = pool.mana_real;
    int mana_max = pool.mana_max;
    int mana_max_level = Mana_max(pool.level);
    draw_bar(x, y, w, h, thickness, MLV_rgba(0, 0, 0, 120),
             (float)mana / mana_max, MLV_rgba(104, 194, 245, 120));
}

static void draw_gem(int x, int y, int w, int h, Gem gem) {
    RGB_Color rgb_color_gem = Color_HSV_to_RGB(gem.color);
    MLV_Color color = RGB_to_MLV_Color(rgb_color_gem, 255);
    MLV_draw_filled_rectangle(x, y, w, h, color);
    MLV_draw_rectangle(x, y, w, h, MLV_COLOR_BLACK);
}

void show_gems(SubWindow window, Inventory inventory, double* actual_pourcent,
               unsigned int page) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    int nb_gems_per_page = 15;
    int gemSize = w * 0.6 / 3;
    int gemSpaceX = w * 0.4 / 4;
    int initial_i = 0 + (page * nb_gems_per_page);
    for (int i = initial_i, j = 0;
         i < inventory.gemstones_count && (i < 15 + (page * initial_i));
         i++, j++) {
        if (j % 3 == 0 && j != 0) {
            *actual_pourcent += 0.1;
            j = 0;
        }
        draw_gem(x + gemSpaceX * (j + 1) + gemSize * j,
                 y + h * (*actual_pourcent), gemSize, gemSize,
                 inventory.gemstones[i]);
    }
}

void show_inventory(SubWindow window, Inventory inventory) {
    int page = 0;
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
    show_gems(window, inventory, &actual_pourcent, page);

    // 20% for the pagination
    actual_pourcent += 0.125;
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "%d/%d",
                       window.font, MLV_COLOR_BLACK, page,
                       inventory.gemstones_count / 15);

    actual_pourcent += 0.075;

    // 1% for the space between the title and the gems
    actual_pourcent += 0.01;
    draw_centered_text(x + w / 2, y + h * actual_pourcent, "Fusion",
                       window.font, MLV_COLOR_BLACK);

    // 5% for the fusion title
    // 1% for the space between the title and the gems
    // 10% for the two gems to fusion
    // 1% for the space between the title and the gems
    // 5% for the button
    // 1% for the space between the title and the gems
}
