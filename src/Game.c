/**
 * @file Game.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 10-01-2024
 *
 */

#include "Game.h"

#include <MLV/MLV_all.h>

#include "Button.h"
#include "ButtonAction.h"
#include "DragAndDrop.h"
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
    srand(time(NULL));
    Error error = NO_ERROR;
    game->has_started = false;
    error.type = inventory_init(&(game->inventory)).type;
    if (error.type)
        return error;
    error.type = Map_init(&(game->map)).type;
    if (error.type)
        return error;
    game->mana_pool = Mana_pool_init();

    while (!Path_gen(&game->map, &game->map.map_turns)) {
        game->map.map_turns.real_len = 0;
    }

    create_windows(game);

    MLV_change_frame_rate(60);

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
}

static void drag_ang_drop_action(Game* game, Event event) {
    static Gem* clicked_gem = NULL;
    static Point new_gem_pos = {0, 0};
    int w = game->window.inventory.width * 0.2;
    int h = game->window.inventory.height * 0.07;
    if (drag_and_drop_gemstone(game, event, &clicked_gem, &new_gem_pos)) {
        draw_gem((Coord_i){new_gem_pos.x - w / 2, new_gem_pos.y - h / 2}, w, h,
                 *clicked_gem);
    }
}

/**
 * @brief Clear all projectiles that target the mob.
 *
 * @param projs DynamicArray of projs.
 * @param mob Target of the projs.
 */
static void _clear_projs_on_target(DynamicArray* projs, Mob* mob) {
    for (int i = 0; i < projs->real_len; i++) {
        if (projs->arr[i].proj.target == mob) {
            DA_remove_index(projs, i--);
        }
    }
}

static void _clear_dead_mob_proj(Game* game) {
    for (int i = 0; i < game->map.mobs.mob_list.real_len; i++) {
        if (game->map.mobs.mob_list.arr[i].mob->current_hp <= 0) {
            _clear_projs_on_target(&(game->map.projs),
                                   game->map.mobs.mob_list.arr[i].mob);
            Mana_gain(
                &(game->mana_pool),
                Mana_gain_mob_death(game->map.mobs.mob_list.arr[i].mob->max_hp,
                                    game->mana_pool.level));
            DA_remove_index(&(game->map.mobs.mob_list), i--);
        }
    }
}

/**
 * @brief Move the wave to the next step.
 *
 * @param wave Wave to move.
 * @param turns Turns of the path.
 * @return if the player is dead.
 *
 */
static bool _wave_next_step(Wave* wave, DynamicArray* turns, ManaPool* pool) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        if (Wave_next_step_unit((wave->mob_list.arr[i].mob), turns)) {
            if (!Mana_buy(pool,
                          Mana_cost_mob_tp(wave->mob_list.arr[i].mob->max_hp,
                                           pool->level))) {
                return true;
            }
        }
    }
    return false;
}

void Game_action(Game* game, Event event) {
    if (event.type == KEYBOARD && event.keyboard.key == MLV_KEYBOARD_SPACE &&
        event.keyboard.state == MLV_PRESSED) {
        if (game->has_started) {
            Mana_gain(
                &(game->mana_pool),
                Mana_gain_skip_wave(game->mana_pool.mana_max,
                                    Wave_skip_to_next(&(game->map.mobs))));
        }
        game->has_started = true;
    }
}

bool Game_update_all(Game* game) {
    if (_wave_next_step(&game->map.mobs, &game->map.map_turns,
                        &game->mana_pool)) {
        return true;
    }
    Map_actualise_proj(&game->map, &game->stats);
    _clear_dead_mob_proj(game);
    Map_towers_shoot(&game->map);
    return false;
}

Error Game_run(Game* game) {
    Error err = NO_ERROR;
    Event event = {NO_EVENT};
    while (!quit_event(event)) {
        Game_action(game, event);
        Game_draw(game);
        event = get_event();
        doing_button_actions(game->buttons, game->window.inventory,
                             game->window.map, game, event);
        drag_ang_drop_action(game, event);

        refresh_window();

        if (Game_update_all(game)) {  // death
            return NO_ERROR;
        }
        if (game->has_started) {
            err.type =
                Wave_spawn_next(&(game->map.mobs),
                                Utils_coord_i_to_f_center(game->map.nest))
                    .type;
        }
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
    button_tab_free(game->buttons);
    font_free(game->window.inventory.font);
    MLV_free_window();
}