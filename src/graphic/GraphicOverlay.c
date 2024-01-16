/**
 * @file GraphicOverlay.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Overlay graphic functions
 * @date 20-11-2023
 *
 */

#include "GraphicOverlay.h"

#include <MLV/MLV_all.h>

#include "Graphic.h"
#include "Mana.h"

/* Draw mana bar */
void draw_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness) {
    int mana = pool.mana_real;
    int mana_max = pool.mana_max;
    MLV_draw_filled_rectangle(x, y, w, h, MLV_rgba(255, 255, 255, 255));
    Coord_i pos = {x, y};
    draw_bar(pos, w, h, thickness, MLV_rgba(0, 0, 0, 255),
             (float)mana / (float)mana_max, MLV_rgba(104, 194, 245, 255));
    draw_centered_text(x + w / 2, y + h / 2, "%d/%d", MLV_COLOR_BLACK, mana,
                       mana_max);
}

void draw_mana_error(int x, int y, int w, int h, int mana_needed, Font* font,
                     MLV_Color color) {
    int text_width;
    int text_height;
    MLV_get_size_of_text_with_font("Not enough mana !", &text_width,
                                   &text_height, font);
    draw_centered_text_with_font(x + w / 2, y + h / 2 - text_height / 2,
                                 "Not enough mana !", font, color);
    draw_centered_text_with_font(x + w / 2, y + h / 2 + text_height / 2,
                                 "Need %d mana", font, color, mana_needed);
}
