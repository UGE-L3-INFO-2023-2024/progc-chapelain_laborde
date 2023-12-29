#include "GraphicMainMenu.h"

#include <MLV/MLV_color.h>

#include "Button.h"
#include "Color.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "Inventory.h"
#include "Mana.h"

void create_inventory_buttons(SubWindow window, ButtonTab* buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* tower_button =
        init_button("tower", (Coord_i){x + w * 0.2, y}, w * 0.3, h * 0.1,
                    MLV_rgba(198, 198, 198, 255));
    button_tab_add(buttons, tower_button);
    Button* mana_button =
        init_button("mana", (Coord_i){x + w * 0.5, y}, w * 0.3, h * 0.1,
                    MLV_rgba(104, 194, 245, 255));
    button_tab_add(buttons, mana_button);
    Button* gem_button =
        init_button("gem", (Coord_i){x + w * 0.35, y + h * 0.11}, w * 0.3,
                    h * 0.1, MLV_rgba(198, 198, 198, 255));
    button_tab_add(buttons, gem_button);
    Button* minus_button =
        init_button("minus", (Coord_i){x + w * 0.18, y + h * 0.14}, w * 0.125,
                    h * 0.04, MLV_rgba(198, 198, 198, 255));
    button_tab_add(buttons, minus_button);
    Button* plus_button =
        init_button("plus", (Coord_i){x + w * 0.68, y + h * 0.14}, w * 0.125,
                    h * 0.04, MLV_rgba(198, 198, 198, 255));
    button_tab_add(buttons, plus_button);
}

static void draw_tower_button(SubWindow window, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* tower = button_tab_get_button(buttons, "tower");
    if (tower != NULL) {
        draw_button(*tower);
        draw_tower(window, NULL, x + w * 0.25, y + w * 0.05, w * 0.2, w * 0.2);
    }
}

static void draw_mana_button(SubWindow window, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* mana = button_tab_get_button(buttons, "mana");
    if (mana != NULL) {
        draw_button(*mana);
        draw_centered_text(x + w * 0.65, y + w * 0.15, "+", window.font,
                           MLV_COLOR_BLACK);
    }
}

static void draw_gem_button(SubWindow window, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* gem = button_tab_get_button(buttons, "gem");
    Button* minus = button_tab_get_button(buttons, "minus");
    Button* plus = button_tab_get_button(buttons, "plus");
    if (gem != NULL && minus != NULL && plus != NULL) {
        draw_button(*gem);
        draw_button(*minus);
        draw_button(*plus);
        draw_centered_text(x + w * 0.24, y + h * 0.155, "-", window.font,
                           MLV_COLOR_BLACK);
        draw_centered_text(x + w * 0.7425, y + h * 0.155, "+", window.font,
                           MLV_COLOR_BLACK);
    }
}

void draw_main_menu(SubWindow window, Inventory inventory, ButtonTab buttons,
                    int gem_level) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    draw_tower_button(window, buttons);
    draw_mana_button(window, buttons);
    draw_gem_button(window, buttons);
    draw_centered_text(x + w / 2, y + h * 0.23, "level : %d", window.font,
                       MLV_COLOR_BLACK, gem_level);
    draw_centered_text(x + w / 2, y + h * 0.27, "cost : %d", window.font,
                       MLV_COLOR_BLACK, Mana_gem_cost(gem_level));
}

void draw_main_menu_bis(SubWindow window) {
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
}