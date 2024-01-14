/**
 * @file GraphicButton.h
 * @author Nathan CHAPELAIN
 * @brief This file contains functions to draw buttons.
 * @date 07-01-2024
 *
 */

#ifndef GRAPHIC_BUTTON_H
#define GRAPHIC_BUTTON_H

#include "Button.h"

#define DEFAULT_BUTTON_COLOR MLV_rgba(198, 198, 198, 255)

/*************/
/* Functions */
/*************/

/**
 * @brief Draw a Button on the screen.
 * To know how to define a button, see the Button structure.
 *
 * @param button The button to draw.
 */
void draw_button(Button button);

#endif  // GRAPHIC_BUTTON_H