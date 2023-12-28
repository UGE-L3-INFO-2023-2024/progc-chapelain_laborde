#include "GraphicMainMenu.h"

#include <MLV/MLV_color.h>

#include "Button.h"
#include "Color.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "Inventory.h"

void create_inventory_buttons(SubWindow window, ButtonTab* buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* tower_button =
        init_button("tower", (Coord_i){x + w * 0.1, y}, w * 0.4, w * 0.4,
                    MLV_rgba(198, 198, 198, 255));
    button_tab_add(buttons, tower_button);
    Button* gemstone_button =
        init_button("mana", (Coord_i){x + w * 0.5, y}, w * 0.4, w * 0.4,
                    MLV_rgba(104, 194, 245, 255));
    button_tab_add(buttons, gemstone_button);
}

void draw_main_menu(SubWindow window, Inventory inventory, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width;
    Button* tower = button_tab_get_button(buttons, "tower");
    if (tower != NULL) {
        draw_button(*tower);
        draw_tower(window, NULL, x + w * 0.15, y + w * 0.05, w * 0.3, w * 0.3);
    }
    Button* mana = button_tab_get_button(buttons, "mana");
    if (mana != NULL) {
        draw_button(*mana);
        draw_centered_text(x + w * 0.7, y + w * 0.2, "+", window.font,
                           MLV_COLOR_BLACK);
    }
}

/* void draw_main_menu(SubWindow window) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    MLV_draw_filled_rectangle(x, y, w, h, CLEAR_COLOR);
    draw_centered_text(x + w / 2, y + h * 0.025, "Tower Defense", window.font,
                       MLV_COLOR_BLACK);
    draw_line(x, y + h * 0.075, x + w, y + h * 0.075, 2, MLV_COLOR_BLACK);
    draw_centered_text(x + w / 2, y + h * 0.125, "Main Menu", window.font,
                       MLV_COLOR_BLACK);
    draw_line(x, y + h * 0.175, x + w, y + h * 0.175, 2, MLV_COLOR_BLACK);
    draw_tower(window, NULL, x + w * 0.1, y + h * 0.2 - w * 0.2, w * 0.2,
               h * 0.2);
    draw_line(x, y + h * 0.375, x + w, y + h * 0.375, 2, MLV_COLOR_BLACK);
    draw_centered_text(x + w / 2, y + h * 0.425, "Buy gems", window.font,
                       MLV_COLOR_BLACK);
    draw_centered_text(x + w * 0.2, y + h * 0.5, "-", window.font,
                       MLV_COLOR_BLACK);
    draw_centered_text(x + w * 0.8, y + h * 0.5, "+", window.font,
                       MLV_COLOR_BLACK);
    draw_centered_text(x + w / 2, y + h * 0.55, "level : %d", window.font,
                       MLV_COLOR_BLACK, 0);
    draw_centered_text(x + w / 2, y + h * 0.6, "cost : %d", window.font,
                       MLV_COLOR_BLACK, 0);
    draw_line(x, y + h * 0.675, x + w, y + h * 0.675, 2, MLV_COLOR_BLACK);
} */