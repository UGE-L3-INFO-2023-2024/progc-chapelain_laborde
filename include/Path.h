/**
 * @file Path.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 11/11/2023
 *
 */

#ifndef __PATH_H__
#define __PATH_H__

#define MIN_TURN 7
#define MIN_LEN 75

#include <stdbool.h>

#include "Map.h"
#include "Utils.h"

int Path_manatan_dist(Coord_i a, Coord_i b);
int Path_manatan_to_border(Coord_i origin, Direction dir,
                           int map_w, int map_h);
int Path_forward_3_4(int max);
void Path_apply_path(Map* map, Coord_i origin, Direction dir, int len);
bool Path_manatan_etentu_cell(Map* map, Coord_i origin, Direction ignore);
int Path_max_dir(Map* map, Coord_i start, Direction dir);
bool Path_gen(Map* map);
void Path_gen_step(Map* map, Coord_i coord, Direction dir, Direction* new_dir, int* new_len);

#endif
