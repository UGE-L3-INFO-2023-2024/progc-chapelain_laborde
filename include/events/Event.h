#ifndef __EVENT_H__
#define __EVENT_H__

#include <MLV/MLV_all.h>
#include <stdbool.h>

typedef enum {
    KEYBOARD,
    MOUSE_MOTION,
    MOUSE_BUTTON,
    NO_EVENT,
} Event_type;

typedef struct {
    MLV_Button_state state;
    MLV_Mouse_button button;
    int x;
    int y;
} Mouse_event;

typedef struct {
    MLV_Button_state state;
    MLV_Keyboard_button key;
} Keyboard_event;

typedef struct {
    Event_type type;
    union {
        Keyboard_event keyboard;
        Mouse_event mouse;
    };
} Event;

/**
 * @brief Get event from the window.
 *
 * @return Event
 */
Event get_event(void);

/**
 * @brief Get the mouse event from the window.
 *
 * @return Event
 */
Event get_mouse_event(void);

/**
 * @brief Get the keyboard event from the window.
 *
 * @return Event
 */
Event get_keyboard_event(void);

/**
 * @brief Check if the event is a quit event.
 *
 * @param event Event to check
 * @return true if user wants to quit
 * @return false otherwise
 */
bool quit_event(Event event);

/**
 * @brief Check if the coordinates are in the rectangle area.
 *
 * @param x X coordinate of the rectangle (top left corner)
 * @param y Y coordinate of the rectangle (top left corner)
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param cible_x X coordinate of the point to check
 * @param cible_y Y coordinate of the point to check
 * @return true if the point is in the rectangle,
 * @return false otherwise
 */
bool is_in_rect_area(int x, int y, int width, int height, int cible_x,
                     int cible_y);

#endif  // __EVENT_H__