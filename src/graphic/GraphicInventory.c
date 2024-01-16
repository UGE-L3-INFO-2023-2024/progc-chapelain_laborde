/**
 * @file GraphicInventory.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Functions to draw inventory menu.
 * @date 12-12-2023
 *
 */

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
 * @brief Draw the given tower on the given position.
 * If img is NULL, draw a circle with tower color instead.
 *
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 * @param x X position of the tower.
 * @param y Y position of the tower.
 * @param width Width of the tower.
 * @param height Height of the tower.
 */
static void draw_tower(MLV_Image* img, int x, int y, int width, int height) {
    if (img) {
        MLV_resize_image(img, width, height);
        MLV_draw_image(img, x, y);
    } else {
        MLV_Color color = MLV_COLOR_BLACK;
        for (int i = 0; i < 3; i++) {
            MLV_draw_filled_rectangle((int)(x + i * width * 0.4), y,
                                      (int)(width * 0.2), (int)(height * 0.3),
                                      color);
        }
        MLV_draw_filled_rectangle((int)(x + 0.15 * width),
                                  (int)(y + height * 0.15), (int)(width * 0.7),
                                  (int)(height * 0.8), color);
        MLV_draw_filled_rectangle(x, (int)(y + height * 0.75), width,
                                  (int)(height * 0.25), color);
    }
}

/**
 * @brief Get the circle point from angle object
 *
 * @param center The center of the circle.
 * @param radius The radius of the circle.
 * @param theta angle in radian.
 * @return Point
 */
static Point get_circle_point_from_angle(Coord_i center, int radius,
                                         double theta) {
    return (Point){.x = (int)(center.x + radius * cos(theta)),
                   .y = (int)(center.y + radius * sin(theta))};
}

/**
 * @brief Create a uniform polygon object coresponding
 *        to his number of points.
 *
 * @param center The center of the polygon.
 * @param radius The radius of the polygon.
 * @param nb_points The number of points of the polygon.
 * @return Polygon
 */
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

/**
 * @brief Draw an empty gem on the screen.
 *
 * @param coord top left corner of the gem
 * @param w width of the gem
 * @param h height of the gem
 */
static void draw_empty_gem(Coord_i coord, int w, int h) {
    MLV_draw_rectangle(coord.x, coord.y, w, h, MLV_COLOR_BLACK);
}

/* Draw a gem with different shape for each level */
void draw_gem(Coord_i coord, int w, int h, Gem gem) {
    MLV_Color mlv_color = RGB_to_MLV_Color(Color_HSV_to_RGB(gem.color), 255);
    Polygon polygon = create_uniform_polygon(
        (Coord_i){coord.x + w / 2, coord.y + h / 2}, w / 2, gem.level + 3);
    draw_filled_polygon(polygon, mlv_color);
    free(polygon.points);
}

/**
 * @brief Create a gem buttons object (upgrade and buying gem)
 *
 * @param window Window to draw on.
 * @param buttons Storage of buttons.
 */
static void create_gem_buttons(SubWindow window, ButtonTab* buttons) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    Button* gem_button =
        Button_init("gem", (Coord_i){(int)(x + w * 0.35), (int)(y + h * 0.11)},
                    (int)(w * 0.3), (int)(h * 0.09), DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, gem_button);
    int minus_plus_width = (int)(w * 0.125);
    int minus_plus_height = (int)(h * 0.04);
    int minus_plus_y = (int)(y + h * 0.135);
    Button* minus_button =
        Button_init("minus", (Coord_i){(int)(x + w * 0.18), minus_plus_y},
                    minus_plus_width, minus_plus_height, DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, minus_button);
    Button* plus_button =
        Button_init("plus", (Coord_i){(int)(x + w * 0.68), minus_plus_y},
                    minus_plus_width, minus_plus_height, DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, plus_button);
}

/**
 * @brief Create a pagination buttons object (gems inventory)
 *
 * @param window window to draw on
 * @param buttons Storage of buttons.
 */
static void create_pagination_buttons(SubWindow window, ButtonTab* buttons) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    int button_width = (int)(w * 0.125);
    int button_height = (int)(h * 0.04);
    int button_y = (int)(y + h * 0.685);
    Button* left_button =
        Button_init("left", (Coord_i){(int)(x + w * 0.15), button_y},
                    button_width, button_height, DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, left_button);
    Button* right_button =
        Button_init("right", (Coord_i){(int)(x + w * 0.735), button_y},
                    button_width, button_height, DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, right_button);
}

/* Create all useful buttons for the sideway part */
void create_inventory_buttons(SubWindow window, ButtonTab* buttons) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    int button_width = (int)(w * 0.3);
    int button_height = (int)(h * 0.09);
    Button* tower_button =
        Button_init("tower", (Coord_i){(int)(x + w * 0.2), (int)(y)},
                    button_width, button_height, DEFAULT_BUTTON_COLOR);
    Button_tab_add(buttons, tower_button);
    Button* mana_button =
        Button_init("mana", (Coord_i){(int)(x + w * 0.5), (int)(y)},
                    button_width, button_height, MLV_rgba(104, 194, 245, 255));
    Button_tab_add(buttons, mana_button);
    create_gem_buttons(window, buttons);
    create_pagination_buttons(window, buttons);
}

/**
 * @brief Draw "buying tower" button.
 *
 * @param window The window to draw on.
 * @param buttons Storage of buttons.
 */
static void draw_tower_button(SubWindow window, ButtonTab buttons) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    const Button* tower = Button_tab_get_button(buttons, "tower");
    if (tower != NULL) {
        draw_button(*tower);
        draw_tower(NULL, (int)(x + w * 0.25), (int)(y + h * 0.015),
                   (int)(w * 0.2), (int)(h * 0.07));
    }
}

/**
 * @brief Draw "Upgrade ManaPool" button.
 *
 * @param window The window to draw on.
 * @param buttons Storage of buttons.
 */
static void draw_mana_button(SubWindow window, ButtonTab buttons) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    const Button* mana = Button_tab_get_button(buttons, "mana");
    if (mana != NULL) {
        draw_button(*mana);
        draw_centered_text_with_font((int)(x + w * 0.65), (int)(y + h * 0.045),
                                     "+", window.font, MLV_COLOR_BLACK);
    }
}

/**
 * @brief Draw "buying gem" button.
 *
 * @param window The window to draw on.
 * @param buttons Storage of buttons.
 * @param gem_level The level of the gem to draw.
 */
static void draw_gem_button(SubWindow window, ButtonTab buttons,
                            int gem_level) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    const Button* gem = Button_tab_get_button(buttons, "gem");
    const Button* minus = Button_tab_get_button(buttons, "minus");
    const Button* plus = Button_tab_get_button(buttons, "plus");
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
        draw_centered_text_with_font((int)(x + w * 0.24), (int)(y + h * 0.150),
                                     "-", window.font, MLV_COLOR_BLACK);
        draw_centered_text_with_font((int)(x + w * 0.7425),
                                     (int)(y + h * 0.150), "+", window.font,
                                     MLV_COLOR_BLACK);
        draw_gem((Coord_i){(int)(x + w * 0.4), (int)(y + h * 0.12)},
                 (int)(w * 0.2), (int)(h * 0.07), gemstone);
        draw_centered_text_with_font((int)(x + w / 2), (int)(y + h * 0.15),
                                     "%d", window.font, MLV_COLOR_BLACK,
                                     gem_level);
    }
}

/**
 * @brief Draw the pagination buttons to navigate in the inventory.
 *
 * @param window The window to draw on.
 * @param buttons Storage of buttons.
 */
static void draw_pagination_buttons(ButtonTab buttons) {
    const Button* left = Button_tab_get_button(buttons, "left");
    const Button* right = Button_tab_get_button(buttons, "right");
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
    int gemSize = (int)(window.width * 0.6 / 3);
    int gemSpace = (int)(window.width * 0.4 / 4);

    for (int i = page * GEMS_PER_PAGE, j = 0;
         i < inventory.gemstones_count &&
         i < GEMS_PER_PAGE + (page * GEMS_PER_PAGE);
         i++, j++) {
        if (j % 3 == 0 && j != 0) {
            height_in_window += 0.1;
            j = 0;
        }
        coord = (Coord_i){
            (int)(window.coord.x + gemSpace * (j + 1) + gemSize * j),
            (int)(window.coord.y + window.height * height_in_window)};
        draw_gem(coord, gemSize, gemSize, inventory.gemstones[i]);
    }
}

/**
 * @brief Draw pagination to navigate in the inventory of gems.
 *
 * @param coord top left corner
 * @param w width
 * @param h height
 * @param font font to use
 * @param page current page
 * @param max_page max page
 */
static void draw_pagination(Coord_i coord, int w, int h, const Font* font,
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
    int text_y = (int)(coord.y + h * height_in_window);
    int margin_x = (int)(w * 0.2);
    draw_centered_text_with_font(coord.x + margin_x, text_y, "<", font,
                                 left_chevron);
    draw_centered_text_with_font(coord.x + w / 2, text_y, "%d/%d", font,
                                 MLV_COLOR_BLACK, page, max_page);
    draw_centered_text_with_font(coord.x + w - margin_x, text_y, ">", font,
                                 right_chevron);
}

/**
 * @brief Draw all gems and pagination to navigate.
 *
 * @param window Window to draw on.
 * @param inventory inventory to draw.
 * @param page current page
 */
static void draw_gems_and_pagination(SubWindow window, Inventory inventory,
                                     unsigned int page) {
    draw_all_gems(window, inventory, page);
    draw_pagination((Coord_i){(int)window.coord.x, (int)window.coord.y},
                    window.width, window.height, window.font, page + 1,
                    ((int)inventory.gemstones_count - 1) / GEMS_PER_PAGE + 1);
}

static void draw_gem_or_empty(Coord_i coord, int w, int h,
                              const Gemstone* gem) {
    if (gem == NULL)
        draw_empty_gem(coord, w, h);
    else
        draw_gem(coord, w, h, *gem);
}

/* @warning Don't forget to change hover_fusion_slot in InventoryEvent if
 * changing this coordinates. */
static void draw_fusion_menu(SubWindow window, Inventory inventory) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    int fusion_width = (int)(w * 0.2);
    int fusion_height = (int)(h * 0.07);
    int fusion_y = (int)(y + h * 0.78);

    draw_gem_or_empty((Coord_i){(int)(x + w * 0.1), fusion_y}, fusion_width,
                      fusion_height, inventory.fusion[0]);
    draw_centered_text_with_font((int)(x + w * 0.35), (int)(y + h * 0.81), "+",
                                 window.font, MLV_COLOR_BLACK);
    draw_gem_or_empty((Coord_i){(int)(x + w * 0.4), fusion_y}, fusion_width,
                      fusion_height, inventory.fusion[1]);
    draw_centered_text_with_font((int)(x + w * 0.65), (int)(y + h * 0.81), "=",
                                 window.font, MLV_COLOR_BLACK);
    draw_gem_or_empty((Coord_i){(int)(x + w * 0.7), fusion_y}, fusion_width,
                      fusion_height, inventory.fusion[2]);
}

/* Draw all inventory interface */
void draw_inventory_menu(SubWindow window, Inventory inventory,
                         ButtonTab buttons, int gem_level, int page) {
    double x = window.coord.x;
    double y = window.coord.y;
    int w = window.width;
    int h = window.height;
    int line_y;
    draw_tower_button(window, buttons);
    draw_mana_button(window, buttons);
    draw_gem_button(window, buttons, gem_level);
    draw_centered_text_with_font((int)(x + w / 2), (int)(y + h * 0.24),
                                 "cost: %d", window.font, MLV_COLOR_BLACK,
                                 Mana_gem_cost(gem_level));
    line_y = (int)(y + h * 0.275);
    draw_line((int)x, line_y, (int)(x + w), line_y, 2, MLV_COLOR_BLACK);
    draw_pagination_buttons(buttons);
    draw_gems_and_pagination(window, inventory, page);
    line_y = (int)(y + h * 0.75);
    draw_line((int)x, line_y, (int)(x + w), line_y, 2, MLV_COLOR_BLACK);
    draw_fusion_menu(window, inventory);
}
