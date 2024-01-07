/**
 * @file Error.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19-11-2023
 *
 */

#include "Error.h"

#include <stdio.h>

void Error_print(Error err, char* func) {
    char* error_msg[NB_ERRORS] = {
        "Dynamic Array Allocation error",
        "Dynamic Array Wrong Type",
        "Dynamic Array Empty",
        "Dynamic Array Wrong Size",
        "Malloc error",
        "Gemstone not found",
    };

    fprintf(stderr, "%s%s in function : %s %s\n", RED, error_msg[err - 1],
            func, RESET);
}
