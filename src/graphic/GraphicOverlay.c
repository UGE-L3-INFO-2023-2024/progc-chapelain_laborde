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

void show_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness) {
    int mana = pool.mana_real;
    int mana_max = pool.mana_max;
    // int mana_max_level = Mana_max(pool.level);
    draw_bar(x, y, w, h, thickness, MLV_rgba(0, 0, 0, 120),
             (float)mana / mana_max, MLV_rgba(104, 194, 245, 120));
}
