#include "Button.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <string.h>

#include "Error.h"
#include "Graphic.h"
#include "Utils.h"

/* Initialize a button with default parameters */
Button* init_button(char* name, Coord_i coord, int width, int height,
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

Error button_tab_init(ButtonTab* buttons) {
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

Error button_tab_add(ButtonTab* buttons, Button* button) {
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

void button_tab_free(ButtonTab buttons) {
    for (unsigned int i = 0; i < buttons.capacity; i++) {
        free(buttons.buttons[i]);
    }
    free(buttons.buttons);
    buttons.buttons = NULL;
}

Button* button_tab_get_button(ButtonTab buttons, char* name) {
    for (unsigned int i = 0; i < buttons.count; i++) {
        if (strcmp(buttons.buttons[i]->name, name) == 0) {
            return buttons.buttons[i];
        }
    }
    return NULL;
}
