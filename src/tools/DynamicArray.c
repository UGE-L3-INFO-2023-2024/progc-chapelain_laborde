/**
 * @file DynamicArray.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19/11/2023
 *
 */

#include "DynamicArray.h"

#include <assert.h>
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
    da->size_alloc = size_alloc;
    da->type = type;
    return CLEAR;
}

Error DA_realloc(DynamicArray* da) {
    int* tmp =
        (int*)realloc(da->arr, (da->max_len * (int)DA_MUL_SIZE_ALLOC) * sizeof(int));
    if (!tmp) {
        free(da->arr);
        da->arr = NULL;
        return DYNA_ARR_ERR_ALLOC;
    }
    da->arr = (DA_Union*)tmp;
    da->max_len *= (int)DA_MUL_SIZE_ALLOC;
    return CLEAR;
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
            da->arr[da->real_len++].project = val.project;
            break;
        default:
            return DYNA_ARR_ERR_TYPE;
    }
    return CLEAR;
}

Error DA_remove(DynamicArray* da, DynamicArray_Union* val,
                Type_array type) {
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
            (*val).path = da->arr[--(da->real_len)].path;
            break;
        case MOB:
            (*val).mob = da->arr[--(da->real_len)].mob;
            break;
        case PROJECTILE:
            (*val).project = da->arr[--(da->real_len)].project;
            break;
        default:
            return DYNA_ARR_ERR_TYPE;
    }

    return CLEAR;
}

void DA_free(DynamicArray da) {
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
                printf("| hp mob: %d |\n", da->arr[i].mob.current_hp);
                break;
            case PROJECTILE:
                printf("| project: WIP |\n");
                break;
            default:
                break;
        }
    }
    printf("|-------------|\n");
}
