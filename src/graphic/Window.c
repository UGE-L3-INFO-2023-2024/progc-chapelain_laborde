/**
 * @file Window.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage window and subwindows.
 * @date 15-11-2023
 *
 */
#include "Window.h"

#include <MLV/MLV_shape.h>
#include <stdlib.h>

#include "Font.h"
#include "Graphic.h"
#include "Utils.h"

/* Initalize the window */
Window Window_init(Coord_f coord, unsigned int width, unsigned int height,
                   Font* font) {
    Window window;
    window.window = NULL;
    window.width = width;
    window.height = height;
    window.font = font;
    window.coord = coord;
    return window;
}

/* Initialize the sub-window */
SubWindow SubWindow_init(Window* window, Coord_f coord, unsigned int width,
                         unsigned int height) {
    SubWindow sub_window;
    sub_window.window = window;
    sub_window.width = width;
    sub_window.height = height;
    sub_window.font = window->font;
    sub_window.coord = coord;
    return sub_window;
}

/* Clear lMLV window */
void clear_window(Window window) {
    MLV_draw_filled_rectangle((int)window.coord.x, (int)window.coord.y,
                              window.width, window.height, CLEAR_COLOR);
}
