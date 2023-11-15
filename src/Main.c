/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Map.h"
#include "Path.h"
#include "Test.h"
#include "Window.h"

int main(int argc, char const *argv[]) {
    Window window = Window_init((Coord_f){0, 0}, 1400, 880);
    srand(time(NULL));
    Map map = Map_init();
    while (!Path_gen(&map)) {
        // Map_print(&map);
        printf("retry\n");
    }

    Map_print(&map);
    printf("finish\n");
    test_graphic_field(map, &window);
    while (1)
        ;
    return 0;
}
