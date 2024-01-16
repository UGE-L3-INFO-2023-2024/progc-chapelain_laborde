/**
 * @file FieldEvent.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Get the event on the field of the game
 * @date 29-12-2023
 *
 */
#include "FieldEvent.h"

#include "DynamicArray.h"
#include "Event.h"
#include "Map.h"
#include "Utils.h"
#include "Window.h"

/* Translate graphics coord inot game coord */
Coord_i get_coord_on_map(SubWindow window, Coord_i coord) {
    return (Coord_i){
        .x = coord.x / (window.width / MAP_WIDTH),
        .y = coord.y / (window.height / MAP_HEIGHT),
    };
}

/* Tells which tower is unde the mouse curor or NULL */
Tower* get_hovered_tower(SubWindow window, Event event, Map map) {
    Coord_i coord =
        get_coord_on_map(window, (Coord_i){event.mouse.x, event.mouse.y});
    for (int i = 0; i < map.towers.real_len; i++) {
        if (Coord_i_equal(map.towers.arr[i].tower.coord, coord)) {
            return (Tower*)DA_get(&map.towers, i);
        }
    }
    return NULL;
}

/* Tells which tower if click or null */
Tower* click_on_tower(SubWindow window, Event event, Map map) {
    if (event.type == MOUSE_BUTTON && event.mouse.state == MLV_PRESSED) {
        return get_hovered_tower(window, event, map);
    }
    return NULL;
}
