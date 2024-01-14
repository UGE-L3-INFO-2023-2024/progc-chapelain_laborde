/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 13-11-2024
 *
 */
#define _XOPEN_SOURCE 600

#include <stdlib.h>

#include "Error.h"
#include "Game.h"

int main(int argc, char const* argv[]) {
    Game game;
    Error err = NO_ERROR;
    err.type = Game_Init(&game).type;
    if (err.type) {
        Game_free(&game);
        Error_print(err);
        return EXIT_FAILURE;
    }
    err.type = Game_run(&game).type;
    if (err.type) {
        Game_free(&game);
        Error_print(err);
        return EXIT_FAILURE;
    }
    Game_free(&game);
    return EXIT_SUCCESS;
}
