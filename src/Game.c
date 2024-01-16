/**
 * @file Game.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains the Game structure and its functions. It's the
 * main module to run the game.
 * @date 09-01-2024
 *
 */

#include "Game.h"

#include <MLV/MLV_all.h>
#include <time.h>

#include "Button.h"
#include "ButtonAction.h"
#include "DragAndDrop.h"
#include "Error.h"
#include "Event.h"
#include "FieldEvent.h"
#include "Graphic.h"
#include "GraphicField.h"
#include "GraphicInventory.h"
#include "GraphicOverlay.h"
#include "Inventory.h"
#include "InventoryEvent.h"
#include "Mana.h"
#include "Map.h"
#include "Path.h"
#include "Stats.h"
#include "TimeManager.h"
#include "Utils.h"
#include "Wave.h"
#include "Window.h"

#define INVENTORY_PROPORTION 0.2

/**
 * @brief Create all used windows (Map, Inventory)
 *
 * @details Create all used windows (Map, Inventory) and set the font of the
 * inventory.
 *
 * @param game Game
 */
static void create_windows(Game* game, int width, int height) {
    game->window.main = Window_init((Coord_f){0, 0}, width, height, NULL);
    MLV_create_window("Gemcraft", "Gemcraft", width, height);
    double inventory_width = width * INVENTORY_PROPORTION;
    double map_width = width - inventory_width;
    game->window.map = SubWindow_init(&game->window.main, (Coord_f){0, 0},
                                      (int)map_width, height);
    game->window.inventory =
        SubWindow_init(&game->window.main, (Coord_f){map_width, 0},
                       (int)inventory_width, height);
    game->window.inventory.font =
        Font_load("assets/fonts/unifont.ttf", (int)inventory_width / 7);
    game->window.map.font =
        Font_load("assets/fonts/unifont.ttf", (int)map_width / 28);
}

/*Initalise the game */
Error Game_Init(Game* game) {
    srand(time(NULL));
    Error error = NO_ERROR;
    game->has_started = false;
    error.type = Inventory_init(&(game->inventory)).type;
    if (error.type)
        return error;
    error.type = Map_init(&(game->map)).type;
    if (error.type)
        return error;
    game->mana_pool = Mana_pool_init();

    while (!Path_gen(&game->map, &game->map.map_turns)) {
        game->map.map_turns.real_len = 0;
    }

    game->stats = Stats_init();

    create_windows(game, 1400, 880);

    MLV_change_frame_rate(FRAMERATE);

    Button_tab_init(&game->buttons);
    create_inventory_buttons(game->window.inventory, &game->buttons);

    game->mana_error = (ManaError){0, Time_get()};
    return NO_ERROR;
}

/* Draw all game */
void Game_draw(const Game* game) {
    draw_map(game->map, game->window.map);
    draw_mana_bar(
        game->mana_pool,
        (int)(game->window.map.coord.x + game->window.map.width * 0.16),
        (int)(game->window.map.coord.y + game->window.map.height * 0.93),
        (int)(game->window.map.width * 0.68),
        (int)(game->window.map.height * 0.045),
        (int)(game->window.map.height * 0.003));
    draw_inventory_menu(game->window.inventory, game->inventory, game->buttons,
                        game->inventory.info.gem_level,
                        game->inventory.info.page);
    draw_mobs((game->map.mobs), game->window.map, NULL);
    if (Time_is_after(Time_get(), game->mana_error.timeout)) {
        draw_mana_error((int)game->window.map.coord.x,
                        (int)game->window.map.coord.y, game->window.map.width,
                        game->window.map.height, game->mana_error.cost,
                        game->window.map.font, MLV_COLOR_RED);
    }
}

/**
 * @brief Draw the gem that is being move.
 *
 * @param game Game
 * @param event Event lMLV
 */
static void _drag_ang_drop_action(Game* game, Event event) {
    static Gem* clicked_gem = NULL;
    static Point new_gem_pos = {0, 0};
    double w = game->window.inventory.width * 0.2;
    double h = game->window.inventory.height * 0.07;
    if (drag_and_drop_gemstone(game, event, &clicked_gem, &new_gem_pos)) {
        Coord_f pos = {new_gem_pos.x - w / 2.0, new_gem_pos.y - h / 2};
        draw_gem(Utils_coord_f_to_i(pos), (int)w, (int)h, *clicked_gem);
    }
}

/**
 * @brief Clear all projectiles that target the mob.
 *
 * @param projs DynamicArray of projs.
 * @param mob Target of the projs.
 */
static void _clear_projs_on_target(DynamicArray* projs, const Mob* mob) {
    for (int i = 0; i < projs->real_len; i++) {
        if (projs->arr[i].proj.target == mob) {
            DA_remove_index(projs, i);
            i--;
        }
    }
}

/**
 * @brief Clear all dead mobs and projectiles who target them.
 *
 * @param game Game
 */
static void _clear_dead_mob_proj(Game* game) {
    for (int i = 0; i < game->map.mobs.mob_list.real_len; i++) {
        if (game->map.mobs.mob_list.arr[i].mob->current_hp <= 0) {
            _clear_projs_on_target(&(game->map.projs),
                                   game->map.mobs.mob_list.arr[i].mob);
            Mana_gain(
                &(game->mana_pool),
                Mana_gain_mob_death(game->map.mobs.mob_list.arr[i].mob->max_hp,
                                    game->mana_pool.level));
            game->stats.mobs_killed++;
            DA_remove_index(&(game->map.mobs.mob_list), i);
            i--;
        }
    }
}

/**
 * @brief Move the wave to the next step.
 *
 * @param game Game
 * @return if the player is dead.
 *
 */
static bool _wave_next_step(Game* game) {
    int dmg = 0;
    for (int i = 0; i < game->map.mobs.mob_list.real_len; i++) {
        if (Wave_next_step_unit(game->map.mobs.mob_list.arr[i].mob,
                                game->map.map_turns, &dmg)) {
            if (Mana_buy(&game->mana_pool,
                         Mana_cost_mob_banish(
                             game->map.mobs.mob_list.arr[i].mob->max_hp,
                             game->mana_pool.level))) {
                game->stats.mana_lost += Mana_cost_mob_banish(
                    game->map.mobs.mob_list.arr[i].mob->max_hp,
                    game->mana_pool.level);
            } else {
                return true;
            }
        }
    }
    game->stats.total_damage += dmg;
    return false;
}

/**
 * @brief Draw the final screen. (score, time, ...)
 *
 * @param game to get the stats.
 * @param start start time of the game.
 */
static void _final_screen(Game* game, struct timespec start) {
    game->stats.timeplayed = Time_ms_interval(start, Time_get()) / 1000;
    game->stats.last_wave = game->map.mobs.nb_wave;
    game->stats.score = game->stats.last_wave * 1000 + game->stats.mobs_killed;
    draw_game_over_screen(game->window.map, game->stats);
    refresh_window();
    Event_wait();
}

/* Keyboard event gestion */
void Game_action(Game* game, Event event) {
    if (event.type == KEYBOARD && event.keyboard.key == MLV_KEYBOARD_SPACE &&
        event.keyboard.state == MLV_PRESSED) {
        if (game->has_started) {
            Mana_gain(&(game->mana_pool),
                      Mana_gain_skip_wave(
                          game->mana_pool.mana_max,
                          (int)Wave_skip_to_next(&(game->map.mobs))));
        }
        game->has_started = true;
    }
}

/* Update all move (side effect update stats) */
bool Game_update_all(Game* game) {
    if (_wave_next_step(game)) {
        return true;
    }
    Map_actualise_proj(&game->map, &game->stats);
    _clear_dead_mob_proj(game);
    Map_towers_shoot(&game->map);
    return false;
}

/* Main loop of execution (event, actualise move, draw) */
Error Game_run(Game* game) {
    struct timespec start = Time_get();
    Error err = NO_ERROR;
    Event event = {NO_EVENT};
    while (!Event_quit(event)) {
        Game_action(game, event);
        Game_draw(game);
        event = Event_get();
        doing_button_actions(game->buttons, game->window.inventory,
                             game->window.map, game, event);
        _drag_ang_drop_action(game, event);

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
    _final_screen(game, start);
    return NO_ERROR;
}

/* Free game */
void Game_free(Game* game) {
    Inventory_free(&(game->inventory));
    Map_free(&(game->map));
    Button_tab_free(game->buttons);
    Font_free(game->window.inventory.font);
    Font_free(game->window.map.font);
    MLV_free_window();
}