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

#endif  // __EVENT_H__