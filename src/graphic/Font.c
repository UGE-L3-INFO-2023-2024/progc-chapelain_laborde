/**
 * @file Font.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Font management.
 * @date 11-12-2023
 *
 */
#include "Font.h"

#include "MLV/MLV_text.h"

/* Load font from a file */
Font Font_load(const char* path, int size) {
    return MLV_load_font(path, size);
}

/* Free font */
void Font_free(Font font) {
    MLV_free_font(font);
}