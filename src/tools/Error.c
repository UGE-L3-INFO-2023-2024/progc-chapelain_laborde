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
        "Allocation error",
        "Stack is empty",
        "Not enough value",
        "Division by 0",
        "Modulo by 0",
        "Negative factorial",
        "Illegal token",
    };

    printf("%s%s in function : %s %s\n", RED, error_msg[err - 1], func, RESET);
}
