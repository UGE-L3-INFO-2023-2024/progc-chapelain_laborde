/**
 * @file Window.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage window and subwindows.
 * @date 30-10-2023
 *
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Font.h"
#include "Utils.h"

/**************/
/* Structures */
/**************/

/**
 * @brief A window is a rectangle on the screen. It is defined by its width,
 * height and the coordinates of its north-west corner.
 * A sub-window is a window that is contained in another window.
 *
 */
typedef struct _window {
    struct _window* window;  // The encapsulating window
    unsigned int width;      // The width of the window
    unsigned int height;     // The height of the window
    Font* font;              // The font to use in the window
    Coord_f coord;           // The north-west corner of the window
} Window, SubWindow;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a window.
 *
 * @param width Width of the window.
 * @param height Height of the window.
 * @param coord Coordinates of the north-west corner of the window.
 * @param font Font to use in the window.
 * @return Window Initialized window.
 */
Window Window_init(Coord_f coord, unsigned int width, unsigned int height,
                   Font* font);

/**
 * @brief Initialize a sub-window. A sub-window is a window that is contained
 * in another window.
 *
 * @param window Encapsulating window (The window that contains the
 * sub-window). This field cannot be NULL.
 * @param coord Coordinates of the north-west corner of the sub-window.
 * @param width Width of the sub-window.
 * @param height Height of the sub-window.
 * @return SubWindow Initialized sub-window.
 */
SubWindow SubWindow_init(Window* window, Coord_f coord, unsigned int width,
                         unsigned int height);

/**
 * @brief This function clear the given window with the CLEAR_COLOR.
 *
 * @param window Window to clear.
 */
void clear_window(Window window);

#endif  // __WINDOW_H__
