#include "Button.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <string.h>

#include "Error.h"
#include "Graphic.h"
#include "Utils.h"

/* Initialize a button with default parameters */
Button* init_button(char* name, Coord_i coord, int width, int height,
                    MLV_Color color) {
    Button* button = malloc(sizeof(Button));
    if (button == NULL) {
        return NULL;
    }
    button->name = name;
    button->coord = coord;
    button->width = width;
    button->height = height;
    button->color = color;
    button->pressed = false;
    return button;
}

/**
 * @brief Draw a triangle on the screen.
 * The triangle is filled with the given color.
 * The triangle is defined by the three given points.
 * The points are given in the order of the drawing.
 *
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param x3 The x coordinate of the third point.
 * @param y3 The y coordinate of the third point.
 * @param color The color of the triangle.
 */
static void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                          MLV_Color color) {
    int vx[3] = {x1, x2, x3};
    int vy[3] = {y1, y2, y3};
    MLV_draw_filled_polygon(vx, vy, 3, color);
}

/**
 * @brief Draw an unpressed button on the screen.
 * The button is filled with the given color.
 * The coordinates are the top left corner of the button.
 *
 * @param x The x coordinate of the button.
 * @param y The y coordinate of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param rect_color The color of the top of the button
 */
static void draw_unpressed_button(int x, int y, int width, int height,
                                  MLV_Color rect_color) {
    draw_triangle(x, y, x, y + height, x + width, y, MLV_COLOR_WHITE);
    draw_triangle(x + width, y, x + width, y + height, x, y + height,
                  MLV_rgba(128, 128, 128, 255));
    MLV_draw_filled_rectangle(x + width / 20, y + height / 20,
                              width - width / 10, height - height / 10,
                              rect_color);
}

/**
 * @brief Draw a pressed button on the screen.
 * The button is filled with the given color.
 * The coordinates are the top left corner of the button.
 *
 * @param x The x coordinate of the button.
 * @param y The y coordinate of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param rect_color The color of the top of the button.
 */
static void draw_pressed_button(int x, int y, int width, int height,
                                MLV_Color rect_color) {
    draw_triangle(x, y, x, y + height, x + width, y,
                  MLV_rgba(128, 128, 128, 255));
    draw_triangle(x + width, y, x + width, y + height, x, y + height,
                  MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(x + width / 20, y + height / 20,
                              width - width / 10, height - height / 10,
                              rect_color);
}

/* Draw a button with states */
void draw_button(Button button) {
    if (button.pressed) {
        draw_pressed_button(button.coord.x, button.coord.y, button.width,
                            button.height, button.color);
    } else {
        draw_unpressed_button(button.coord.x, button.coord.y, button.width,
                              button.height, button.color);
    }
}

Error button_tab_init(ButtonTab* buttons) {
    buttons->buttons = malloc(sizeof(Button*) * 3);
    if (buttons->buttons == NULL) {
        return MALLOC_ERR;
    }
    buttons->count = 0;
    buttons->capacity = 3;
    return CLEAR;
}

Error button_tab_add(ButtonTab* buttons, Button* button) {
    if (buttons->count == buttons->capacity) {
        buttons->capacity *= 2;
        buttons->buttons =
            realloc(buttons->buttons, sizeof(Button*) * buttons->capacity);
        if (buttons->buttons == NULL) {
            return MALLOC_ERR;
        }
    }
    buttons->buttons[buttons->count++] = button;
    return CLEAR;
}

void button_tab_free(ButtonTab buttons) {
    for (unsigned int i = 0; i < buttons.capacity; i++) {
        free(buttons.buttons[i]);
    }
    free(buttons.buttons);
    buttons.buttons = NULL;
}

Button* button_tab_get_button(ButtonTab buttons, char* name) {
    for (unsigned int i = 0; i < buttons.count; i++) {
        if (strcmp(buttons.buttons[i]->name, name) == 0) {
            return buttons.buttons[i];
        }
    }
    return NULL;
}
