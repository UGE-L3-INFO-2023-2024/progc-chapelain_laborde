#include "InventoryEvent.h"

#include <stdbool.h>

#include "Button.h"
#include "Event.h"

bool is_in_rect_area(int x, int y, int width, int height, int cible_x,
                     int cible_y) {
    return cible_x >= x && cible_x <= x + width && cible_y >= y &&
           cible_y <= y + height;
}

bool click_in_inventory(Event event, SubWindow inventory_window) {
    return event.type == MOUSE_BUTTON &&
           is_in_rect_area(inventory_window.coord.x, inventory_window.coord.y,
                           inventory_window.width, inventory_window.height,
                           event.mouse.x, event.mouse.y);
}

bool click_on_text(SubWindow window, Event event, const char* text, int x,
                   int y) {
    int font_width, font_height;
    MLV_get_size_of_text_with_font(text, &font_width, &font_height,
                                   window.font);
    return event.type == MOUSE_BUTTON &&
           is_in_rect_area(x, y, font_width, font_height, event.mouse.x,
                           event.mouse.y);
}

bool click_on_centered_text(SubWindow window, Event event, const char* text,
                            int x, int y) {
    int font_width, font_height;
    MLV_get_size_of_text_with_font(text, &font_width, &font_height,
                                   window.font);
    return click_on_text(window, event, text, x - font_width / 2,
                         y - font_height / 2);
}

bool click_left_arrow(SubWindow inventory_window, Event event) {
    return click_in_inventory(event, inventory_window) &&
           click_on_centered_text(
               inventory_window, event, "<",
               inventory_window.coord.x + inventory_window.width * 0.2,
               inventory_window.coord.y + inventory_window.height * 0.630);
}

bool click_right_arrow(SubWindow inventory_window, Event event) {
    return click_in_inventory(event, inventory_window) &&
           click_on_centered_text(
               inventory_window, event, ">",
               inventory_window.coord.x + inventory_window.width * 0.8,
               inventory_window.coord.y + inventory_window.height * 0.630);
}

bool click_on_button(SubWindow window, Event event, Button button) {
    return event.type == MOUSE_BUTTON &&
           is_in_rect_area(button.coord.x, button.coord.y, button.width,
                           button.height, event.mouse.x, event.mouse.y);
}