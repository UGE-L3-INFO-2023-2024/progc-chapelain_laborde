/**
 * @file Button.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Manage graphic buttons (array, init, add, get from name, free)
 * @date 07-01-2024
 *
 */

#include "Button.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <string.h>

#include "Error.h"
#include "Graphic.h"
#include "Utils.h"

/* Initialize a button with default parameters */
Button* Button_init(char* name, Coord_i coord, int width, int height,
                    MLV_Color color) {
    Button* button = malloc(sizeof(Button));
    if (button == NULL) {
        return NULL;
    }
    button->name = name;
    button->coord = coord;
    button->width = width;
    button->height = height;
    button->color = color;
    button->pressed = false;
    return button;
}

/* Initialise array of button */
Error Button_tab_init(ButtonTab* buttons) {
    Error err = NO_ERROR;
    buttons->buttons = malloc(sizeof(Button*) * 3);
    if (buttons->buttons == NULL) {
        err.type = MALLOC_ERR;
        return err;
    }
    buttons->count = 0;
    buttons->capacity = 3;
    return NO_ERROR;
}

/* Add a button to the array */
Error Button_tab_add(ButtonTab* buttons, Button* button) {
    Error err = NO_ERROR;
    if (buttons->count == buttons->capacity) {
        buttons->capacity *= 2;
        buttons->buttons =
            realloc(buttons->buttons, sizeof(Button*) * buttons->capacity);
        if (buttons->buttons == NULL) {
            err.type = MALLOC_ERR;
            return err;
        }
    }
    buttons->buttons[buttons->count++] = button;
    return NO_ERROR;
}

/* Free array of button */
void Button_tab_free(ButtonTab buttons) {
    for (int i = 0; i < buttons.count; i++) {
        free(buttons.buttons[i]);
        buttons.buttons[i] = NULL;
    }
    free(buttons.buttons);
    buttons.buttons = NULL;
}

/* Get button from his name */
Button* Button_tab_get_button(ButtonTab buttons, char* name) {
    for (int i = 0; i < buttons.count; i++) {
        if (strcmp(buttons.buttons[i]->name, name) == 0) {
            return buttons.buttons[i];
        }
    }
    return NULL;
}
