/**
 * @file DynamicArray.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage a dynamic array (generic allocated array).
 * @date 19-11-2023
 *
 */

#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include "Error.h"
#include "Mob.h"
#include "Projectile.h"
#include "Tower.h"
#include "Utils.h"

#define DA_MUL_SIZE_ALLOC 1.5

/**************/
/* Structures */
/**************/

typedef enum {
    PATH,
    MOB,
    PROJECTILE,
    TOWER,
} Type_array;

typedef union {
    Mob* mob;
    Projectile proj;
    Coord_i path;
    Tower tower;
} DynamicArray_Union, DA_Union;

typedef struct {
    int real_len;
    int max_len;
    Type_array type;
    DA_Union* arr;
} DynamicArray;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a DynamicArray.
 *
 * @param da DynamicArray to initialize.
 * @param size_alloc Size of the DynamicArray.
 * @param type Type of the DynamicArray.
 * @return if there is a allocation error.
 */
Error DA_init(DynamicArray* da, int size_alloc, Type_array type);

/**
 * @brief Realloc a DynamicArray to inrease his size.
 *
 * @param da DynamicArray to realloc.
 * @return if there is a allocation error.
 */
Error DA_realloc(DynamicArray* da);

/**
 * @brief Get a value from a DynamicArray.
 *
 * @param da DynamicArray to get the value.
 * @param index Index of the value.
 * @return DynamicArray_Union* Value.
 */
DynamicArray_Union* DA_get(DynamicArray* da, int index);

/**
 * @brief Add a value to a DynamicArray.
 *
 * @param da DynamicArray to add the value.
 * @param val Value to add.
 * @param type Type of the the value.
 * @return if there is a allocation error or a missmatch type.
 */
Error DA_add(DynamicArray* da, DynamicArray_Union val, Type_array type);

/**
 * @brief Remove last value from a DynamicArray.
 *
 * @param da DynamicArray to remove the value.
 * @param val Value removed.
 * @param type Type of the the value.
 * @return if there is a missmatch type or an empty DynamicArray.
 */
Error DA_remove_last(DynamicArray* da, DynamicArray_Union* val,
                     Type_array type);

/**
 * @brief Remove index value from a DynamicArray.
 *
 * @param da DynamicArray to remove the value.
 * @param index Index to remove in the array.
 * @return if there is a missmatch type or an empty DynamicArray or
 *         an index out of range.
 */
Error DA_remove_index(DynamicArray* da, int index);

/**
 * @brief Free a DynamicArray.
 *
 * @param da DynamicArray to free.
 */
void DA_free(DynamicArray da);

/**
 * @brief Print a DynamicArray. (Debug Function)
 *
 * @param da DynamicArray to print.
 */
void DA_print_all(DynamicArray* da);

#endif  // _DYNAMICARRAY_H_