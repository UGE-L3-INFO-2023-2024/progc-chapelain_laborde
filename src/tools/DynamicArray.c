/**
 * @file DynamicArray.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19-11-2023
 *
 */

#include "DynamicArray.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Error.h"

Error DA_init(DynamicArray* da, int size_alloc, Type_array type) {
    // alloc array
    da->arr = (DA_Union*)malloc(size_alloc * sizeof(DynamicArray_Union));
    if (!(da->arr)) {
        return DYNA_ARR_ERR_ALLOC;
    }
    // init other values
    da->max_len = size_alloc;
    da->real_len = 0;
    da->type = type;
    return CLEAR;
}

Error DA_realloc(DynamicArray* da) {
    assert(da);
    assert(da->arr);

    int new_size = da->max_len * DA_MUL_SIZE_ALLOC;
    DA_Union* tmp = realloc(da->arr, new_size * sizeof(DA_Union));
    // not enough memory
    if (!tmp) {
        free(da->arr);
        da->arr = NULL;
        return DYNA_ARR_ERR_ALLOC;
    }
    // realloc ok
    da->arr = (DA_Union*)tmp;
    da->max_len = new_size;
    return CLEAR;
}

DynamicArray_Union* DA_get(DynamicArray* da, int index) {
    assert(da);
    assert(da->arr);

    // out of bound
    if (index < 0 || index >= da->real_len) {
        return NULL;
    }
    return da->arr + index;
}

Error DA_add(DynamicArray* da, DynamicArray_Union val, Type_array type) {
    assert(da);
    assert(da->arr);
    if (type != da->type) {
        return DYNA_ARR_ERR_TYPE;
    }

    // realloc if needed
    if (da->real_len == da->max_len) {
        Error err = DA_realloc(da);
        if (err) {
            return err;
        }
    }
    // switch to match the type
    switch (type) {
        case PATH:
            da->arr[da->real_len++].path = val.path;
            break;
        case MOB:
            da->arr[da->real_len++].mob = val.mob;
            break;
        case PROJECTILE:
            da->arr[da->real_len++].proj = val.proj;
            break;
        case TOWER:
            da->arr[da->real_len++].tower = val.tower;
            break;
        default:  // should never happen (new type added)
            return DYNA_ARR_ERR_TYPE;
    }
    return CLEAR;
}

Error DA_remove_last(DynamicArray* da, DynamicArray_Union* val,
                     Type_array type) {
    assert(da);
    assert(da->arr);

    if (type != da->type) {
        return DYNA_ARR_ERR_TYPE;
    }

    if (!da->real_len) {
        return DYNA_ARR_ERR_EMPTY;
    }
    // for the return value
    switch (type) {
        case PATH:
            val->path = da->arr[--(da->real_len)].path;
            break;
        case MOB:
            val->mob = da->arr[--(da->real_len)].mob;
            break;
        case PROJECTILE:
            val->proj = da->arr[--(da->real_len)].proj;
            break;
        case TOWER:
            val->tower = da->arr[--(da->real_len)].tower;
            break;
        default:  // should never happen (new type added)
            return DYNA_ARR_ERR_TYPE;
    }

    return CLEAR;
}

Error DA_remove_index(DynamicArray* da, int index) {
    assert(da);
    assert(da->arr);

    // out of bound or empty
    if (!da->real_len) {
        return DYNA_ARR_ERR_EMPTY;
    }
    if (index > da->real_len || index < 0) {
        return DYNA_ARR_ERR_SIZE;
    }

    // remove the value (switch last to the index and decrement real_len)
    if (da->type == MOB) {
        free(da->arr[index].mob);
    }
    da->arr[index] = da->arr[--(da->real_len)];
    return CLEAR;
}

void DA_free(DynamicArray da) {
    // in case of a mob array (mob are allocated)
    if (da.type == MOB) {
        for (int i = 0; i < da.real_len; i++) {
            free(da.arr[i].mob);
        }
    }
    free(da.arr);
}

void DA_print_all(DynamicArray* da) {
    // debug function who print all the array
    assert(da);
    assert(da->arr);

    printf("\n|-------------|\n");
    for (int i = da->real_len - 1; i >= 0; --i) {
        switch (da->type) {
            case PATH:
                printf("| path: %d,%d |\n", da->arr[i].path.x,
                       da->arr[i].path.y);
                break;
            case MOB:
                printf("| hp mob: %d |\n", da->arr[i].mob->current_hp);
                break;
            case PROJECTILE:
                printf("| project: coord %f,%f color:%d|\n",
                       da->arr[i].proj.pos.x, da->arr[i].proj.pos.y,
                       da->arr[i].proj.gem.color);
                break;
            case TOWER:
                printf("| tower: coord %d,%d hasgem: %d|\n",
                       da->arr[i].tower.coord.x, da->arr[i].tower.coord.y,
                       da->arr[i].tower.has_gem);
                break;
            default:
                break;
        }
    }
    printf("|-------------|\n");
}