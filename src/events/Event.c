#include "Event.h"

Event get_mouse_event() {
    Event event;
    MLV_Button_state mouse_state;
    MLV_Mouse_button mouse_button;
    int mouse_x, mouse_y;
    MLV_Event mlv_event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mouse_x,
                                        &mouse_y, &mouse_button, &mouse_state);
    if (mlv_event == MLV_MOUSE_MOTION || mlv_event == MLV_MOUSE_BUTTON) {
        if (mlv_event == MLV_MOUSE_MOTION) {
            event.type = MOUSE_MOTION;
        } else {
            event.type = MOUSE_BUTTON;
        }
        event.mouse.x = mouse_x;
        event.mouse.y = mouse_y;
        event.mouse.button = mouse_button;
        event.mouse.state = mouse_state;
    } else {
        event.type = NO_EVENT;
    }
    return event;
}

Event get_keyboard_event() {
    Event event;
    MLV_Keyboard_button keyboard_button;
    MLV_Button_state state;
    MLV_Event mlv_event = MLV_get_event(&keyboard_button, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, &state);
    if (mlv_event == MLV_KEY) {
        event.type = KEYBOARD;
        event.keyboard.key = keyboard_button;
        event.keyboard.state = state;
    } else {
        event.type = NO_EVENT;
    }
    return event;
}

Event get_event() {
    Event event = {.type = NO_EVENT};
    MLV_Keyboard_button keyboard_button;
    MLV_Button_state state;
    MLV_Mouse_button mouse_button;
    int mouse_x, mouse_y;
    MLV_Event mlv_event =
        MLV_get_event(&keyboard_button, NULL, NULL, NULL, NULL, &mouse_x,
                      &mouse_y, &mouse_button, &state);
    MLV_flush_event_queue();
    if (mlv_event == MLV_KEY) {
        event.type = KEYBOARD;
        event.keyboard.key = keyboard_button;
        event.keyboard.state = state;
    } else if (mlv_event == MLV_MOUSE_MOTION ||
               mlv_event == MLV_MOUSE_BUTTON) {
        if (mlv_event == MLV_MOUSE_MOTION) {
            event.type = MOUSE_MOTION;
        } else {
            event.type = MOUSE_BUTTON;
        }
        event.mouse.x = mouse_x;
        event.mouse.y = mouse_y;
        event.mouse.button = mouse_button;
        event.mouse.state = state;
    } else {
        event.type = NO_EVENT;
    }
    return event;
}

bool quit_event(Event event) {
    return event.type == KEYBOARD &&
           (event.keyboard.key == MLV_KEYBOARD_q ||
            event.keyboard.key == MLV_KEYBOARD_ESCAPE);
}

bool is_in_rect_area(int x, int y, int width, int height, int cible_x,
                     int cible_y) {
    return cible_x >= x && cible_x <= x + width && cible_y >= y &&
           cible_y <= y + height;
}

bool drop_item(Event event, bool is_dragging) {
    if (is_dragging && event.type == MOUSE_BUTTON &&
        event.mouse.button == MLV_BUTTON_LEFT &&
        event.mouse.state == MLV_RELEASED) {
        return true;
    }
    return false;
}

bool drag_item(Event event, bool *is_dragging, int *old_mouse_x,
               int *old_mouse_y) {
    if (!*is_dragging && event.type == MOUSE_BUTTON &&
        event.mouse.button == MLV_BUTTON_LEFT &&
        event.mouse.state == MLV_PRESSED) {
        *is_dragging = true;
        *old_mouse_x = event.mouse.x;
        *old_mouse_y = event.mouse.y;
    }
    return *is_dragging;
}
