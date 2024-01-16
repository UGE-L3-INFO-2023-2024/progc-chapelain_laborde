/**
 * @file InventoryEvent.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Event functions for the inventory.
 * @date 28-12-2023
 *
 */

#include "InventoryEvent.h"

#include <stdbool.h>

#include "Button.h"
#include "Event.h"
#include "Inventory.h"

/* Check if the mouse is over the inventory space */
bool hovered_inventory(Event event, SubWindow inventory_window) {
    return is_in_rect_area((int)(inventory_window.coord.x),
                           (int)(inventory_window.coord.y),
                           inventory_window.width, inventory_window.height,
                           event.mouse.x, event.mouse.y);
}

/*Check if the click is in the inventory space */
bool click_in_inventory(Event event, SubWindow inventory_window) {
    return event.type == MOUSE_BUTTON &&
           hovered_inventory(event, inventory_window);
}

/**
 * @brief Check if the click is on the text.
 *
 * @param window Window where the font is.
 * @param event Event lMLV (mouse click)
 * @param text Text to check
 * @param x coord of the text height
 * @param y coord of the text width
 * @return if the click is on the text
 */
static bool click_on_text(SubWindow window, Event event, const char* text,
                          int x, int y) {
    int font_width;
    int font_height;
    MLV_get_size_of_text_with_font(text, &font_width, &font_height,
                                   window.font);
    return event.type == MOUSE_BUTTON &&
           is_in_rect_area(x, y, font_width, font_height, event.mouse.x,
                           event.mouse.y);
}

/**
 * @brief Check if the click is the centered text.
 *
 * @param window Window where the font is.
 * @param event Event lMLV (mouse click)
 * @param text Text to check
 * @param x coord of the text height
 * @param y coord of the text width
 * @return if the click is on the text
 */
static bool click_on_centered_text(SubWindow window, Event event,
                                   const char* text, int x, int y) {
    int font_width;
    int font_height;
    MLV_get_size_of_text_with_font(text, &font_width, &font_height,
                                   window.font);
    return click_on_text(window, event, text, x - font_width / 2,
                         y - font_height / 2);
}

/* Check if the click is on the left arrow */
bool click_left_arrow(SubWindow inventory_window, Event event) {
    return click_in_inventory(event, inventory_window) &&
           click_on_centered_text(
               inventory_window, event, "<",
               (int)(inventory_window.coord.x + inventory_window.width * 0.2),
               (int)(inventory_window.coord.y +
                     inventory_window.height * 0.630));
}

/* Check if the click is on the right arrow */
bool click_right_arrow(SubWindow inventory_window, Event event) {
    return click_in_inventory(event, inventory_window) &&
           click_on_centered_text(
               inventory_window, event, ">",
               (int)(inventory_window.coord.x + inventory_window.width * 0.8),
               (int)(inventory_window.coord.y +
                     inventory_window.height * 0.630));
}

/* Check if the click is in a button */
bool click_on_button(Event event, Button button) {
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
        // Here we check if the user clicked on a rectangle
        if (is_in_rect_area(coord.x, coord.y, gemSize, gemSize, event.mouse.x,
                            event.mouse.y)) {
            return inventory.gemstones + i;
        }
    }
    return NULL;
}

/* Check if a gemstone is clicked */
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
    int slotSizeX = (int)(window.width * 0.2);
    int slotSizeY = (int)(window.height * 0.07);
    int slotSpace = (int)(window.width * 0.1);
    for (int i = 0; i < 3; i++) {
        if (is_in_rect_area(
                (int)(window.coord.x + slotSpace * (i + 1) + slotSizeX * i),
                (int)(window.coord.y + window.height * 0.78), slotSizeX,
                slotSizeY, event.mouse.x, event.mouse.y)) {
            *slot = i;
            return true;
        }
    }
    return false;
}

/* return wich slot is mouse over or -1 */
int get_hovered_fusion_slot(SubWindow window, Event event) {
    int slot = -1;
    hover_fusion_slot(&slot, window, event);
    return slot;
}

/* return which slot is clicked or -1 */
int click_on_fusion_slot(SubWindow window, Event event) {
    int slotSizeX = (int)(window.width * 0.2);
    int slotSizeY = (int)(window.height * 0.07);
    int slotSpace = (int)(window.width * 0.1);
    if (event.type != MOUSE_BUTTON || event.mouse.state != MLV_PRESSED) {
        return -1;
    }
    for (int i = 0; i < 3; i++) {
        if (is_in_rect_area(
                (int)(window.coord.x + slotSpace * (i + 1) + slotSizeX * i),
                (int)(window.coord.y + window.height * 0.78), slotSizeX,
                slotSizeY, event.mouse.x, event.mouse.y)) {
            return i;
        }
    }
    return -1;
}
