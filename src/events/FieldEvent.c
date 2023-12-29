#include "FieldEvent.h"

#include "Map.h"
#include "Utils.h"
#include "Window.h"

Coord_i get_coord_on_map(Map map, SubWindow window, Coord_i coord) {
    return (Coord_i){
        .x = coord.x / (window.width / MAP_WIDTH),
        .y = coord.y / (window.height / MAP_HEIGHT),
    };
}