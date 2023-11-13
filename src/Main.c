/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 02/11/2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Map.h"
#include "../include/Path.h"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    Map map = Map_init();
    while (!Path_gen(&map)) {
        // Map_print(&map);
        printf("retry\n");
    }

    Map_print(&map);
    printf("finish\n");
    return 0;
}
