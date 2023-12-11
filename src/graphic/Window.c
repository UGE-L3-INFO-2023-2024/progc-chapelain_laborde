/**
 * @file Window.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */
#include "Window.h"

#include <stdlib.h>

/* Initalize the window */
Window Window_init(Coord_f coord, unsigned int width, unsigned int height) {
    Window window;
    window.window = NULL;
    window.width = width;
    window.height = height;
    window.font = NULL;
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
