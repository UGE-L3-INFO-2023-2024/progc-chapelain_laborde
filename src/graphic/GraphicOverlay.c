/**
 * @file GraphicOverlay.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Overlay graphic functions
 * @date 2023-11-20
 *
 */

#include "GraphicOverlay.h"

#include <MLV/MLV_all.h>

#include "Graphic.h"
#include "Mana.h"

void draw_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness) {
    int mana = pool.mana_real;
    int mana_max = pool.mana_max;
    MLV_draw_filled_rectangle(x, y, w, h, MLV_rgba(255, 255, 255, 255));
    draw_bar(x, y, w, h, thickness, MLV_rgba(0, 0, 0, 255),
             (float)mana / mana_max, MLV_rgba(104, 194, 245, 255));
    draw_centered_text(x + w / 2, y + h / 2, "%d/%d", MLV_COLOR_BLACK, mana,
                       mana_max);
}
