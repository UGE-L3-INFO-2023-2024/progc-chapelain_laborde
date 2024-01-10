#include "InventoryEvent.h"

#include <stdbool.h>

#include "Button.h"
#include "Event.h"
#include "Inventory.h"

bool hovered_inventory(Event event, SubWindow inventory_window) {
    return is_in_rect_area(inventory_window.coord.x, inventory_window.coord.y,
                           inventory_window.width, inventory_window.height,
                           event.mouse.x, event.mouse.y);
}

bool click_in_inventory(Event event, SubWindow inventory_window) {
    return event.type == MOUSE_BUTTON &&
           hovered_inventory(event, inventory_window);
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

/**
 * @brief This function is used to check if the user hover a gemstone with the
 * mouse.
 * If the user didn't hover a gemstone, it returns NULL.
 * This function is used in click_on_gemstone.
 *
 * @param window The subwindow where the gems are displayed.
 * @param event The event to check.
 * @param inventory The inventory to retrieve the gemstones from.
 * @param page The current page of the inventory
 * @return Gemstone* The gemstone hovered.
 */
static Gemstone* hovered_gem(SubWindow window, Event event,
                             Inventory inventory, unsigned int page) {
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
        // Here we check if the user clicked on a rectangle
        // TODO 500: check with gemstone shape instead of rectangle
        if (is_in_rect_area(coord.x, coord.y, gemSize, gemSize, event.mouse.x,
                            event.mouse.y)) {
            return inventory.gemstones + i;
        }
    }
    return NULL;
}

Gemstone* click_on_gemstone(SubWindow window, Event event, Inventory inventory,
                            unsigned int page) {
    if (!click_in_inventory(event, window)) {
        return NULL;
    }
    if (event.type == MOUSE_BUTTON && event.mouse.state == MLV_PRESSED) {
        return hovered_gem(window, event, inventory, page);
    }
    return NULL;
}

/* @warning Don't forget to change draw_fusion_menu in graphicInventory if
 * change this coord. */
bool hover_fusion_slot(int* slot, SubWindow window, Event event) {
    int slotSizeX = window.width * 0.2;
    int slotSizeY = window.height * 0.07;
    int slotSpace = window.width * 0.1;
    for (int i = 0; i < 3; i++) {
        if (is_in_rect_area(
                window.coord.x + slotSpace * (i + 1) + slotSizeX * i,
                window.coord.y + window.height * 0.78, slotSizeX, slotSizeY,
                event.mouse.x, event.mouse.y)) {
            *slot = i;
            return true;
        }
    }
    return false;
}

int get_hovered_fusion_slot(SubWindow window, Event event) {
    int slot = -1;
    hover_fusion_slot(&slot, window, event);
    return slot;
}

int click_on_fusion_slot(SubWindow window, Event event) {
    int slotSizeX = window.width * 0.2;
    int slotSizeY = window.height * 0.07;
    int slotSpace = window.width * 0.1;
    if (event.type != MOUSE_BUTTON || event.mouse.state != MLV_PRESSED) {
        return -1;
    }
    for (int i = 0; i < 3; i++) {
        if (is_in_rect_area(
                window.coord.x + slotSpace * (i + 1) + slotSizeX * i,
                window.coord.y + window.height * 0.78, slotSizeX, slotSizeY,
                event.mouse.x, event.mouse.y)) {
            return i;
        }
    }
    return -1;
}
