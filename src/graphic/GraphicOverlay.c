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
#include "Stats.h"

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

/* Draw the errors of mana */
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

static void _draw_played_time(int x, int y, Font* font, MLV_Color color,
                              long timeplayed) {
    long hours = timeplayed / 3600;
    int minutes = (timeplayed % 3600) / 60;
    int seconds = timeplayed % 60;
    if (hours > 0) {
        draw_centered_text_with_font(x, y, "Time played : %dh %dm", font,
                                     color, hours, minutes);
    } else if (minutes > 0) {
        draw_centered_text_with_font(x, y, "Time played : %dm %ds", font,
                                     color, minutes, seconds);
    } else {
        draw_centered_text_with_font(x, y, "Time played : %ds", font, color,
                                     seconds);
    }
}

/* Draw the stats of the player */
void draw_game_over_screen(SubWindow map_window, Stats stats) {
    int text_height;
    int text_width;
    MLV_get_size_of_text_with_font("Game Over", &text_width, &text_height,
                                   map_window.font);
    int total_text_height = text_height * 8;  // Il y a 8 lignes de texte
    int start_y = map_window.height / 2 - total_text_height / 2;
    MLV_Color text_color = MLV_rgba(235, 235, 235, 255);

    MLV_draw_filled_rectangle(0, 0, map_window.width, map_window.height,
                              MLV_rgba(0, 0, 0, 100));

    draw_centered_text_with_font(map_window.width / 2, start_y, "Game Over",
                                 map_window.font, text_color);
    draw_line(map_window.width / 2 - text_width / 2, start_y + text_height / 2,
              map_window.width / 2 + text_width / 2, start_y + text_height / 2,
              (int)(map_window.height * 0.004), text_color);
    draw_centered_text_with_font(map_window.width / 2, start_y + text_height,
                                 "You survived %d waves", map_window.font,
                                 text_color, stats.last_wave);
    draw_centered_text_with_font(map_window.width / 2,
                                 start_y + text_height * 2,
                                 "You killed %d enemies", map_window.font,
                                 text_color, stats.mobs_killed);
    draw_centered_text_with_font(map_window.width / 2,
                                 start_y + text_height * 3, "You lost %d mana",
                                 map_window.font, text_color, stats.mana_lost);
    draw_centered_text_with_font(map_window.width / 2,
                                 start_y + text_height * 4, "Your score : %d",
                                 map_window.font, text_color, stats.score);
    _draw_played_time(map_window.width / 2, start_y + text_height * 5,
                      map_window.font, text_color, stats.timeplayed);
    draw_centered_text_with_font(
        map_window.width / 2, start_y + text_height * 6, "You did %d damage",
        map_window.font, text_color, stats.total_damage);
}
