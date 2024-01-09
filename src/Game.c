/**
 * @file Game.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 09-01-2024
 *
 */

#include "Game.h"

#include "ButtonAction.h"
#include "Error.h"
#include "Event.h"
#include "FieldEvent.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "GraphicOverlay.h"
#include "Inventory.h"
#include "InventoryEvent.h"
#include "Mana.h"
#include "Map.h"
#include "Path.h"

static void create_windows(Game* game) {
    game->window.main = Window_init((Coord_f){0, 0}, 1400, 880);
    MLV_create_window("Gemcraft", "Gemcraft", game->window.main.width,
                      game->window.main.height);
    game->window.map =
        SubWindow_init(&game->window.main, (Coord_f){0, 0}, 1120, 880);
    game->window.inventory =
        SubWindow_init(&game->window.main, (Coord_f){1120, 0}, 280, 880);
    game->window.inventory.font = font_load("assets/fonts/unifont.ttf",
                                            game->window.inventory.width / 7);
}

Error Game_Init(Game* game) {
    Error error = NO_ERROR;
    error.type = inventory_init(&(game->inventory)).type;
    if (error.type)
        return error;
    error.type = Map_init(&(game->map)).type;
    if (error.type)
        return error;
    game->mana_pool = Mana_pool_init();

    srand(time(NULL));

    while (!Path_gen(&game->map, &game->map.map_turns)) {
        game->map.map_turns.real_len = 0;
    }

    create_windows(game);

    MLV_change_frame_rate(60);
    Wave_next_step(&game->map.mobs, &game->map.map_turns);

    button_tab_init(&game->buttons);
    create_inventory_buttons(game->window.inventory, &game->buttons);

    return NO_ERROR;
}

void Game_draw(Game* game) {
    draw_map(game->map, game->window.map);
    draw_mana_bar(game->mana_pool, 180, 810, 760, 40, 3);
    draw_inventory_menu(game->window.inventory, game->inventory, game->buttons,
                        game->inventory.info.gem_level,
                        game->inventory.info.page);
    draw_mobs(&(game->map.mobs), game->window.map, NULL);
    refresh_window();
}

Error Game_run(Game* game) {
    Error err = NO_ERROR;
    Event event = {NO_EVENT};
    Tower* clicked_tower = NULL;
    Gem* clicked_gem = NULL;
    int slot = -1;
    while (!quit_event(event)) {
        event = get_event();
        doing_button_actions(game->buttons, game->window.inventory,
                             game->window.map, game, event);

        // TODO 0 : Refactor this
        // *********************************************************************
        if (clicked_gem == NULL)
            clicked_gem =
                click_on_gemstone(game->window.inventory, event,
                                  game->inventory, game->inventory.info.page);
        slot = click_on_fusion_slot(game->window.inventory, event);
        if (slot != -1 && clicked_gem != NULL) {
            if (slot == 0 || slot == 1) {
                if (game->inventory.fusion[slot] != NULL)
                    inventory_add_gemstone(&game->inventory,
                                           *game->inventory.fusion[slot]);
                game->inventory.fusion[slot] = Gemstone_copy_ptr(clicked_gem);
                inventory_remove_gemstone(&game->inventory, *clicked_gem);
                clicked_gem = NULL;
            }
        }
        if (slot == 2 && clicked_gem == NULL) {
            if (game->inventory.fusion[0] != NULL &&
                game->inventory.fusion[1] != NULL) {
                if (Gemstone_merge(game->inventory.fusion[0],
                                   game->inventory.fusion[1])) {
                    inventory_add_gemstone(&game->inventory,
                                           *game->inventory.fusion[0]);
                    free(game->inventory.fusion[0]);
                    free(game->inventory.fusion[1]);
                    game->inventory.fusion[0] = NULL;
                    game->inventory.fusion[1] = NULL;
                }
            }
        }
        clicked_tower = click_on_tower(game->window.map, event, game->map);
        if (clicked_tower != NULL && clicked_gem != NULL) {
            if (clicked_tower->has_gem) {
                Gem tower_gem;
                Tower_extract_gem(clicked_tower, &tower_gem);
                inventory_add_gemstone(&game->inventory, tower_gem);
            }
            Tower_add_gem(clicked_tower, clicked_gem);
            inventory_remove_gemstone(&game->inventory, *clicked_gem);
            clicked_gem = NULL;
        }

        // *********************************************************************

        Game_draw(game);
        Wave_next_step(&game->map.mobs, &game->map.map_turns);
        Map_towers_shoot(&game->map);
        Map_actualise_proj(&game->map);
        err.type = Wave_spawn_next(&(game->map.mobs),
                                   Utils_coord_i_to_f_center(game->map.nest))
                       .type;
        if (err.type) {
            return err;
        }

        MLV_delay_according_to_frame_rate();
    }
    return NO_ERROR;
}

void Game_free(Game* game) {
    inventory_free(&(game->inventory));
    Map_free(&(game->map));
}