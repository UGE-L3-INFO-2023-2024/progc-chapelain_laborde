#include "FieldEvent.h"

#include "DynamicArray.h"
#include "Event.h"
#include "Map.h"
#include "Utils.h"
#include "Window.h"

Coord_i get_coord_on_map(Map map, SubWindow window, Coord_i coord) {
    return (Coord_i){
        .x = coord.x / (window.width / MAP_WIDTH),
        .y = coord.y / (window.height / MAP_HEIGHT),
    };
}

Tower* get_hovered_tower(SubWindow window, Event event, Map map) {
    Coord_i coord =
        get_coord_on_map(map, window, (Coord_i){event.mouse.x, event.mouse.y});
    for (int i = 0; i < map.towers.real_len; i++) {
        if (Coord_i_equal(map.towers.arr[i].tower.coord, coord)) {
            return (Tower*)DA_get(&map.towers, i);
        }
    }
    return NULL;
}

Tower* click_on_tower(SubWindow window, Event event, Map map) {
    if (event.type == MOUSE_BUTTON && event.mouse.state == MLV_PRESSED) {
        return get_hovered_tower(window, event, map);
    }
    return NULL;
}
