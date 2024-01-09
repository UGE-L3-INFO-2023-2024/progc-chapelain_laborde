/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 07-01-2024
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

/*  Event event = {NO_EVENT};
 Tower* clicked_tower = NULL;
 Gem* clicked_gem = NULL;
 int slot = -1;
 while (!quit_event(event)) {
     event = get_event();
     doing_button_actions(game.buttons, game.window.inventory,
                          game.window.map, &game, event);
     if (clicked_gem == NULL)
         clicked_gem =
             click_on_gemstone(game.window.inventory, event,
 game.inventory, game.inventory.info.page); slot =
 click_on_fusion_slot(game.window.inventory, event); if (slot != -1 &&
 clicked_gem != NULL) { if (slot == 0 || slot == 1) { if
 (game.inventory.fusion[slot] != NULL)
                 inventory_add_gemstone(&game.inventory,
                                        *game.inventory.fusion[slot]);
             game.inventory.fusion[slot] = Gemstone_copy_ptr(clicked_gem);
             inventory_remove_gemstone(&game.inventory, *clicked_gem);
             clicked_gem = NULL;
         }
     }
     if (slot == 2 && clicked_gem == NULL) {
         if (game.inventory.fusion[0] != NULL &&
             game.inventory.fusion[1] != NULL) {
             if (Gemstone_merge(game.inventory.fusion[0],
                                game.inventory.fusion[1])) {
                 inventory_add_gemstone(&game.inventory,
                                        *game.inventory.fusion[0]);
                 free(game.inventory.fusion[0]);
                 free(game.inventory.fusion[1]);
                 game.inventory.fusion[0] = NULL;
                 game.inventory.fusion[1] = NULL;
             }
         }
     }
     clicked_tower = click_on_tower(game.window.map, event, game.map);
     if (clicked_tower != NULL && clicked_gem != NULL) {
         if (clicked_tower->has_gem) {
             Gem tower_gem;
             Tower_extract_gem(clicked_tower, &tower_gem);
             inventory_add_gemstone(&game.inventory, tower_gem);
         }
         Tower_add_gem(clicked_tower, clicked_gem);
         inventory_remove_gemstone(&game.inventory, *clicked_gem);
         clicked_gem = NULL;
     }
     Game_draw(&game);
     Wave_next_step(&game.map.mobs, &game.map.map_turns);
     Map_towers_shoot(&game.map);
     Map_actualise_proj(&game.map);
     err = Wave_spawn_next(&(game.map.mobs),
                           Utils_coord_i_to_f_center(game.map.nest));
     if (err.type) {
         Error_print(err);
         return EXIT_FAILURE;
     }

     MLV_delay_according_to_frame_rate();
 } */
