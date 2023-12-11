#include "Font.h"

#include "MLV/MLV_text.h"

Font font_load(const char* path, int size) {
    return MLV_load_font(path, size);
}

void font_free(Font font) {
    MLV_free_font(font);
}