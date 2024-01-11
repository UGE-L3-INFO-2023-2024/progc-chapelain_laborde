#include "GraphicInventory.h"

#include <MLV/MLV_color.h>

#include "Button.h"
#include "Color.h"
#include "Graphic.h"
#include "GraphicButton.h"
#include "Inventory.h"
#include "Mana.h"
#include "Utils.h"
#include "math.h"

/**
 * @brief Draw the given tower on the given window.
 * If img is NULL, draw a circle with tower color instead.
 *
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 * @param x X position of the tower.
 * @param y Y position of the tower.
 * @param width Width of the tower.
 * @param height Height of the tower.
 */
static void draw_tower(SubWindow window, MLV_Image* img, int x, int y,
                       int width, int height) {
    if (img) {
        MLV_resize_image(img, width, height);
        MLV_draw_image(img, x, y);
    } else {
        MLV_Color color = MLV_COLOR_BLACK;
        for (int i = 0; i < 3; i++) {
            MLV_draw_filled_rectangle(x + i * width * 0.4, y, width * 0.2,
                                      height * 0.3, color);
        }
        MLV_draw_filled_rectangle(x + 0.15 * width, y + height * 0.15,
                                  width * 0.7, height * 0.8, color);
        MLV_draw_filled_rectangle(x, y + height * 0.75, width, height * 0.25,
                                  color);
    }
}

static Point get_circle_point_from_angle(Coord_i center, int radius,
                                         double theta) {
    return (Point){.x = center.x + radius * cos(theta),
                   .y = center.y + radius * sin(theta)};
}

static Polygon create_uniform_polygon(Coord_i center, int radius,
                                      int nb_points) {
    Polygon polygon = {.nb_points = 0};
    Point* points = malloc(sizeof(Point) * nb_points);
    for (int i = 0; i < nb_points; i++) {
        points[i] = get_circle_point_from_angle(
            center, radius,
            Utils_deg_to_rad(360 / nb_points * i) - HOME_PI / 2);
    }
    polygon = (Polygon){.points = points, .nb_points = nb_points};
    return polygon;
}

static void draw_empty_gem(Coord_i coord, int w, int h, int level) {
    MLV_draw_rectangle(coord.x, coord.y, w, h, MLV_COLOR_BLACK);
}

void draw_gem(Coord_i coord, int w, int h, Gem gem) {
    MLV_Color mlv_color = RGB_to_MLV_Color(Color_HSV_to_RGB(gem.color), 255);
    Polygon polygon = create_uniform_polygon(
        (Coord_i){coord.x + w / 2, coord.y + h / 2}, w / 2, gem.level + 3);
    draw_filled_polygon(polygon, mlv_color);
    free(polygon.points);
}

static void create_gem_buttons(SubWindow window, ButtonTab* buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* gem_button =
        init_button("gem", (Coord_i){x + w * 0.35, y + h * 0.11}, w * 0.3,
                    h * 0.09, DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, gem_button);
    Button* minus_button =
        init_button("minus", (Coord_i){x + w * 0.18, y + h * 0.135}, w * 0.125,
                    h * 0.04, DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, minus_button);
    Button* plus_button =
        init_button("plus", (Coord_i){x + w * 0.68, y + h * 0.135}, w * 0.125,
                    h * 0.04, DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, plus_button);
}

static void create_pagination_buttons(SubWindow window, ButtonTab* buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* left_button =
        init_button("left", (Coord_i){x + w * 0.15, y + h * 0.685}, w * 0.125,
                    h * 0.04, DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, left_button);
    Button* right_button =
        init_button("right", (Coord_i){x + w * 0.735, y + h * 0.685},
                    w * 0.125, h * 0.04, DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, right_button);
}

void create_inventory_buttons(SubWindow window, ButtonTab* buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* tower_button =
        init_button("tower", (Coord_i){x + w * 0.2, y}, w * 0.3, h * 0.09,
                    DEFAULT_BUTTON_COLOR);
    button_tab_add(buttons, tower_button);
    Button* mana_button =
        init_button("mana", (Coord_i){x + w * 0.5, y}, w * 0.3, h * 0.09,
                    MLV_rgba(104, 194, 245, 255));
    button_tab_add(buttons, mana_button);
    create_gem_buttons(window, buttons);
    create_pagination_buttons(window, buttons);
}

static void draw_tower_button(SubWindow window, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* tower = button_tab_get_button(buttons, "tower");
    if (tower != NULL) {
        draw_button(*tower);
        draw_tower(window, NULL, x + w * 0.25, y + h * 0.015, w * 0.2,
                   w * 0.2);
    }
}

static void draw_mana_button(SubWindow window, ButtonTab buttons) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* mana = button_tab_get_button(buttons, "mana");
    if (mana != NULL) {
        draw_button(*mana);
        draw_centered_text_with_font(x + w * 0.65, y + h * 0.045, "+",
                                     window.font, MLV_COLOR_BLACK);
    }
}

static void draw_gem_button(SubWindow window, ButtonTab buttons,
                            int gem_level) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Button* gem = button_tab_get_button(buttons, "gem");
    Button* minus = button_tab_get_button(buttons, "minus");
    Button* plus = button_tab_get_button(buttons, "plus");
    static int old_level = -1;
    static Gem gemstone;
    if (gem_level != old_level) {
        old_level = gem_level;
        gemstone = Gemstone_init(gem_level);
    }
    if (gem != NULL && minus != NULL && plus != NULL) {
        draw_button(*gem);
        draw_button(*minus);
        draw_button(*plus);
        draw_centered_text_with_font(x + w * 0.24, y + h * 0.150, "-",
                                     window.font, MLV_COLOR_BLACK);
        draw_centered_text_with_font(x + w * 0.7425, y + h * 0.150, "+",
                                     window.font, MLV_COLOR_BLACK);
        draw_gem((Coord_i){x + w * 0.4, y + h * 0.12}, w * 0.2, h * 0.07,
                 gemstone);
        draw_centered_text_with_font(x + w / 2, y + h * 0.15, "%d",
                                     window.font, MLV_COLOR_BLACK, gem_level);
    }
}

static void draw_pagination_buttons(SubWindow window, ButtonTab buttons) {
    Button* left = button_tab_get_button(buttons, "left");
    Button* right = button_tab_get_button(buttons, "right");
    if (left != NULL && right != NULL) {
        draw_button(*left);
        draw_button(*right);
    }
}

/**
 * @brief Draw all the gems of the inventory on the screen.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory containing the gems to draw.
 * @param page The page of the inventory gems to draw.
 * Page start at 0 not 1.
 */
static void draw_all_gems(SubWindow window, Inventory inventory,
                          unsigned int page) {
    double height_in_window = 0.3;
    Coord_i coord;
    int gemSize = window.width * 0.6 / 3;
    int gemSpace = window.width * 0.4 / 4;

    for (int i = page * GEMS_PER_PAGE, j = 0;
         i < inventory.gemstones_count &&
         i < GEMS_PER_PAGE + (page * GEMS_PER_PAGE);
         i++, j++) {
        if (j % 3 == 0 && j != 0) {
            height_in_window += 0.1;
            j = 0;
        }
        coord = (Coord_i){window.coord.x + gemSpace * (j + 1) + gemSize * j,
                          window.coord.y + window.height * height_in_window};
        draw_gem(coord, gemSize, gemSize, inventory.gemstones[i]);
    }
}

static void draw_pagination(Coord_i coord, int w, int h, Font font,
                            unsigned int page, unsigned int max_page) {
    double height_in_window = 0.7;
    MLV_Color left_chevron = MLV_COLOR_BLACK;
    MLV_Color right_chevron = MLV_COLOR_BLACK;
    if (page == 1) {
        left_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    if (max_page == page) {
        right_chevron = MLV_COLOR_LIGHT_GRAY;
    }
    draw_centered_text_with_font(coord.x + w * 0.2,
                                 coord.y + h * height_in_window, "<", font,
                                 left_chevron);
    draw_centered_text_with_font(coord.x + w / 2,
                                 coord.y + h * height_in_window, "%d/%d", font,
                                 MLV_COLOR_BLACK, page, max_page);
    draw_centered_text_with_font(coord.x + w * 0.8,
                                 coord.y + h * height_in_window, ">", font,
                                 right_chevron);
}

static void draw_gems_and_pagination(SubWindow window, Inventory inventory,
                                     unsigned int page) {
    draw_all_gems(window, inventory, page);
    draw_pagination((Coord_i){window.coord.x, window.coord.y}, window.width,
                    window.height, window.font, page + 1,
                    ((int)inventory.gemstones_count - 1) / GEMS_PER_PAGE + 1);
}

/* @warning Don't forget to change hover_fusion_slot in InventoryEvent if
 * changing this coordinates. */
static void draw_fusion_menu(SubWindow window, Inventory inventory) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    Gemstone *slot1 = inventory.fusion[0], *slot2 = inventory.fusion[1];
    if (slot1 == NULL)
        draw_empty_gem((Coord_i){x + w * 0.1, y + h * 0.78}, w * 0.2, h * 0.07,
                       1);
    else
        draw_gem((Coord_i){x + w * 0.1, y + h * 0.78}, w * 0.2, h * 0.07,
                 *slot1);
    draw_centered_text_with_font(x + w * 0.35, y + h * 0.81, "+", window.font,
                                 MLV_COLOR_BLACK);
    if (slot2 == NULL)
        draw_empty_gem((Coord_i){x + w * 0.4, y + h * 0.78}, w * 0.2, h * 0.07,
                       1);
    else
        draw_gem((Coord_i){x + w * 0.4, y + h * 0.78}, w * 0.2, h * 0.07,
                 *slot2);
    draw_centered_text_with_font(x + w * 0.65, y + h * 0.81, "=", window.font,
                                 MLV_COLOR_BLACK);
    if (inventory.fusion[2] != NULL) {
        draw_gem((Coord_i){x + w * 0.7, y + h * 0.78}, w * 0.2, h * 0.07,
                 *inventory.fusion[2]);
    } else {
        draw_empty_gem((Coord_i){x + w * 0.7, y + h * 0.78}, w * 0.2, h * 0.07,
                       1);
    }
}

void draw_inventory_menu(SubWindow window, Inventory inventory,
                         ButtonTab buttons, int gem_level, int page) {
    int x = window.coord.x, y = window.coord.y;
    int w = window.width, h = window.height;
    draw_tower_button(window, buttons);
    draw_mana_button(window, buttons);
    draw_gem_button(window, buttons, gem_level);
    draw_centered_text_with_font(x + w / 2, y + h * 0.24, "cost: %d",
                                 window.font, MLV_COLOR_BLACK,
                                 Mana_gem_cost(gem_level));
    draw_line(x, y + h * 0.275, x + w, y + h * 0.275, 2, MLV_COLOR_BLACK);
    draw_pagination_buttons(window, buttons);
    draw_gems_and_pagination(window, inventory, page);
    draw_line(x, y + h * 0.75, x + w, y + h * 0.75, 2, MLV_COLOR_BLACK);
    draw_fusion_menu(window, inventory);
}
