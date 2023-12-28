#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <stdio.h>

#define CLEAR_COLOR MLV_COLOR_WHITE

bool is_in_rect_area(int x, int y, int width, int height, int cible_x,
                     int cible_y) {
    return cible_x >= x && cible_x <= x + width && cible_y >= y &&
           cible_y <= y + height;
}

bool is_in_polygon_area(const int* vx, const int* vy, int nb_points, int x,
                        int y) {
    int i, j;
    bool c = false;
    for (i = 0, j = nb_points - 1; i < nb_points; j = i++) {
        if (((vy[i] > y) != (vy[j] > y)) &&
            (x < (vx[j] - vx[i]) * (y - vy[i]) / (vy[j] - vy[i]) + vx[i])) {
            c = !c;
        }
    }
    return c;
}

bool quit_event(MLV_Keyboard_button keysym) {
    return keysym == MLV_KEYBOARD_q || keysym == MLV_KEYBOARD_ESCAPE;
}

bool drag(MLV_Mouse_button button, MLV_Button_state state) {
    return button == MLV_BUTTON_LEFT && state == MLV_PRESSED;
}

bool drop(MLV_Mouse_button button, MLV_Button_state state) {
    return button == MLV_BUTTON_LEFT && state == MLV_RELEASED;
}

void clear_polygon(const int* vx, const int* vy, int nb_points) {
    MLV_draw_filled_polygon(vx, vy, nb_points, CLEAR_COLOR);
}

void move_polygon(int* vx, int* vy, int nb_points, int dx, int dy) {
    int i;
    for (i = 0; i < nb_points; i++) {
        vx[i] += dx;
        vy[i] += dy;
    }
}

bool drag_and_drop_polygon(int* vx, int* vy, int nb_points,
                           MLV_Mouse_button* mouse_button,
                           MLV_Button_state* mouse_state) {
    if (drag(*mouse_button, *mouse_state)) {
        int mouse_x, mouse_y;
        MLV_get_mouse_position(&mouse_x, &mouse_y);
        if (is_in_polygon_area(vx, vy, nb_points, mouse_x, mouse_y)) {
            int prev_x = mouse_x, prev_y = mouse_y;
            int dx, dy;
            while (1) {
                MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mouse_x, &mouse_y,
                              mouse_button, mouse_state);
                if (drop(*mouse_button, *mouse_state)) {
                    return true;
                }
                dx = mouse_x - prev_x;
                dy = mouse_y - prev_y;
                prev_x = mouse_x;
                prev_y = mouse_y;
                clear_polygon(vx, vy, nb_points);
                move_polygon(vx, vy, nb_points, dx, dy);
                MLV_draw_filled_polygon(vx, vy, nb_points, MLV_COLOR_BLACK);
                MLV_actualise_window();
            }
        }
    }
    return false;
}

bool drag_and_drop_rectangle(int* x, int* y, int w, int h,
                             MLV_Mouse_button* mouse_button,
                             MLV_Button_state* mouse_state) {
    int vx[4] = {*x, *x + w, *x + w, *x};
    int vy[4] = {*y, *y, *y + h, *y + h};
    bool tmp = drag_and_drop_polygon(vx, vy, 4, mouse_button, mouse_state);
    *x = vx[0];
    *y = vy[0];
    return tmp;
}

int main(int argc, char const* argv[]) {
    MLV_create_window("Test", "Test", 1400, 880);
    int x = 500, y = 100;
    int width = 40, height = 40;
    MLV_Keyboard_button keysym;
    MLV_Mouse_button mouse_button;
    MLV_Button_state mouse_state;
    // Losange
    int vx[4] = {100, 200, 100, 0};
    int vy[4] = {0, 100, 200, 100};
    while (1) {
        MLV_draw_filled_rectangle(x, y, width, height, MLV_COLOR_BLACK);
        MLV_draw_filled_polygon(vx, vy, 4, MLV_COLOR_BLACK);
        MLV_actualise_window();
        MLV_get_event(&keysym, NULL, NULL, NULL, NULL, NULL, NULL,
                      &mouse_button, &mouse_state);
        if (drag_and_drop_rectangle(&x, &y, width, height, &mouse_button,
                                    &mouse_state)) {
            printf("drop\n");
        }
        if (drag_and_drop_polygon(vx, vy, 4, &mouse_button, &mouse_state)) {
            printf("drop\n");
        }
        if (quit_event(keysym)) {
            break;
        }
        MLV_wait_milliseconds(10);
        MLV_clear_window(MLV_COLOR_WHITE);
    }
    MLV_free_window();
    return 0;
}
