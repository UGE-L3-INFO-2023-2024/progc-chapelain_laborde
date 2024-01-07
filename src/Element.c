/**
 * @file Element.c
 * @author Laborde Quentin
 * @brief
 * @date 07-01-2024
 *
 */

#include "Element.h"

Element Elem_init(void) {
    return (Element){
        .main = NONE,
        .second = NONE,
    };
}