/**
 * @file DynamicArray.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19/11/2023
 *
 */

#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <Mob.h>
#include <Projectile.h>
#include <Utils.h>

typedef enum {
    PATH,
    MOB,
    PROJECTILE,
} Type_array;

typedef union {
    Mob mob;
    Projectile project;
    Coord_i path;
} DynamicArray_Union, DA_Union;

typedef struct {
    int real_len;
    int max_len;
    Type_array type;
    DA_Union* arr;
    int size_alloc;
} DynamicArray;

/**
 * @brief Initialize a DynamicArray.
 *
 * @param da DynamicArray to initialize.
 * @param size_alloc Size of the DynamicArray.
 * @param type Type of the DynamicArray.
 * @return if there is a allocation error.
 */
Error Stack_init(DynamicArray* da, int size_alloc, Type_array type);

/**
 * @brief Realloc a DynamicArray to inrease his size.
 *
 * @param da DynamicArray to realloc.
 * @return if there is a allocation error.
 */
Error Stack_realloc(DynamicArray* da);

/**
 * @brief Add a value to a DynamicArray.
 *
 * @param da DynamicArray to add the value.
 * @param val Value to add.
 * @param type Type of the the value.
 * @return if there is a allocation error or a missmatch type.
 */
Error Stack_add(DynamicArray* da, DynamicArray_Union val, Type_array type);

/**
 * @brief Remove a value from a DynamicArray.
 *
 * @param da DynamicArray to remove the value.
 * @param val Value to remove.
 * @param type Type of the the value.
 * @return if there is a missmatch type or an empty DynamicArray.
 */
Error Stack_remove(DynamicArray* da, DynamicArray_Union* val, Type_array type);

/**
 * @brief Free a DynamicArray.
 *
 * @param da DynamicArray to free.
 */
void Stack_free(DynamicArray da);

/**
 * @brief Print a DynamicArray.
 *
 * @param da DynamicArray to print.
 */
void Stack_print_all(DynamicArray* da);

#endif  // _DYNAMICARRAY_H_