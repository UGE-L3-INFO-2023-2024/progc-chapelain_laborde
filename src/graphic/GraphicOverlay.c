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
    printf("rgb_color_gem: %d %d %d\n", rgb_color_gem.r, rgb_color_gem.g,
           rgb_color_gem.b);
    MLV_Color color = RGB_to_MLV_Color(rgb_color_gem, 255);
    MLV_draw_filled_rectangle(x, y, w, h, color);
    MLV_draw_rectangle(x, y, w, h, MLV_COLOR_BLACK);
}

void show_inventory(SubWindow window, Inventory inventory) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;

    // 5% for the title
    MLV_draw_text_with_font(x + 50, y, "Inventory", window.font,
                            MLV_COLOR_BLACK);

    // 1% for the space between the title and the gems

    // 60% for the gems
    int gemSize = w * 0.6 / 3;
    int gemSpace = w * 0.4 / 4;
    for (int i = 0; i < inventory.gemstones_count; i++) {
        draw_gem(x + gemSpace + (gemSize + gemSpace) * i, y + h * 0.05,
                 gemSize, gemSize, inventory.gemstones[i]);
    }

    // 10% for the space between gems
    // 1% for the space between the title and the gems

    // 5% for the fusion title
    // 1% for the space between the title and the gems
    // 10% for the two gems to fusion
    // 1% for the space between the title and the gems
    // 5% for the button
    // 1% for the space between the title and the gems
}
