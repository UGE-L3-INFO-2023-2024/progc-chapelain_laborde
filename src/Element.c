/**
 * @file Element.c
 * @author Laborde Quentin
 * @brief Manage element creation and store effects constants.
 * @date 07-01-2024
 *
 */

#include "Element.h"

/* Initalise element */
Element Elem_init(void) {
    return (Element){
        .main = NONE,
        .second = NONE,
        .origin_dmg = 0,
    };
}