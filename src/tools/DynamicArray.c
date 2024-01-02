/**
 * @file DynamicArray.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19/11/2023
 *
 */

#include "DynamicArray.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Utils.h"

Error DA_init(DynamicArray* da, int size_alloc, Type_array type) {
    da->arr = (DA_Union*)malloc(size_alloc * sizeof(DynamicArray_Union));
    if (!(da->arr)) {
        return DYNA_ARR_ERR_ALLOC;
    }
    da->max_len = size_alloc;
    da->real_len = 0;
    da->type = type;
    return CLEAR;
}

Error DA_realloc(DynamicArray* da) {
    int new_size = da->max_len * DA_MUL_SIZE_ALLOC;
    printf("realloc before %d after %d\n", da->max_len, new_size);
    printf("realloc size %ld type : %d\n", new_size * sizeof(DA_Union), da->type);
    DA_Union* tmp = realloc(da->arr, new_size * sizeof(DA_Union));
    if (!tmp) {
        free(da->arr);
        da->arr = NULL;
        return DYNA_ARR_ERR_ALLOC;
    }
    da->arr = (DA_Union*)tmp;
    da->max_len = new_size;
    return CLEAR;
}

DynamicArray_Union* DA_get(DynamicArray* da, int index) {
    assert(da);
    assert(da->arr);
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

    if (da->real_len == da->max_len) {
        Error err = DA_realloc(da);
        if (err) {
            return err;
        }
    }
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
        default:
            return DYNA_ARR_ERR_TYPE;
    }
    return CLEAR;
}

Error DA_remove_last(DynamicArray* da, DynamicArray_Union* val, Type_array type) {
    assert(da);
    assert(da->arr);

    if (type != da->type) {
        return DYNA_ARR_ERR_TYPE;
    }

    if (!da->real_len) {
        return DYNA_ARR_ERR_EMPTY;
    }

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
        default:
            return DYNA_ARR_ERR_TYPE;
    }

    return CLEAR;
}

Error DA_remove_index(DynamicArray* da, int index) {
    assert(da);
    assert(da->arr);

    if (!da->real_len) {
        return DYNA_ARR_ERR_EMPTY;
    }
    if (index > da->real_len || index < 0) {
        return DYNA_ARR_ERR_SIZE;
    }

    da->arr[index] = da->arr[--(da->real_len)];
    return CLEAR;
}

void DA_free(DynamicArray da) {
    if (da.type == MOB) {
        for (int i = 0; i < da.real_len; i++) {
            free(da.arr[i].mob);
        }
    }
    free(da.arr);
}

void DA_print_all(DynamicArray* da) {
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
                printf("| project: WIP |\n");
                break;
            case TOWER:
                printf("| tower: WIP |\n");
                break;
            default:
                break;
        }
    }
    printf("|-------------|\n");
}