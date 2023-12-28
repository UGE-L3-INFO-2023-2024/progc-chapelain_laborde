#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <MLV/MLV_color.h>
#include <stdbool.h>

#include "Error.h"
#include "Utils.h"

/**
 * @brief A button is a rectangle with a text inside.
 *
 */
typedef struct {
    char* name;       // Name of the button. Cannot be NULL and must be unique.
    Coord_i coord;    // The top left corner of the button.
    int width;        // The width of the button.
    int height;       // The height of the button.
    MLV_Color color;  // The color of the top of the button.
    bool pressed;     // True if the button is pressed.
} Button;

typedef struct {
    Button** buttons;
    unsigned int count;
    unsigned int capacity;
} ButtonTab;

/**
 * @brief Draw a Button on the screen.
 * To know how to define a button, see the Button structure.
 *
 * @param button The button to draw.
 */
void draw_button(Button button);

/**
 * @brief Initialize a button.
 * The button is set by default to not pressed.
 *
 * @param name The name of the button.
 * @param coord The top left corner of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param color The color of the top of the button.
 * @return Button The initialized button.
 */
Button* init_button(char* name, Coord_i coord, int width, int height,
                    MLV_Color color);

/**
 * @brief Initialize the buttons of an inventory.
 *
 * @param inventory The inventory to initialize the buttons of.
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error button_tab_init(ButtonTab* inventory);

/**
 * @brief Add a button to the inventory.
 *
 * @param inventory The inventory to add the button to.
 * @param button The button to add.
 *
 * @return Error CLEAR if no error occured, MALLOC_ERR otherwise.
 */
Error button_tab_add(ButtonTab* inventory, Button* button);

/**
 * @brief Free the buttons of an inventory.
 *
 * @param inventory The inventory to free the buttons of.
 */
void button_tab_free(ButtonTab inventory);

/**
 * @brief Get a button from an inventory.
 * If there is no button with the given name, NULL is returned.
 * If there are multiple buttons with the same name, the first one is returned.
 *
 * @param inventory The inventory to get the button from.
 * @param name The name of the button to get.
 * @return Button* The button if it exists, NULL otherwise.
 */
Button* button_tab_get_button(ButtonTab inventory, char* name);

#endif  // __BUTTON_H__