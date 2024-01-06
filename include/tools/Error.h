/**
 * @file Error.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19-11-2023
 *
 */

#ifndef __ERROR_H__
#define __ERROR_H__

/***************/
/* Error Color */
/***************/

#define RESET "\033[0m"
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */

/**************/
/* Structures */
/**************/

#define NB_ERRORS 5

typedef enum {
    CLEAR = 0,
    DYNA_ARR_ERR_ALLOC = 1,
    DYNA_ARR_ERR_TYPE = 2,
    DYNA_ARR_ERR_EMPTY = 3,
    DYNA_ARR_ERR_SIZE = 4,
    MALLOC_ERR = 5,
} Error;

/*************/
/* Functions */
/*************/

/**
 * @brief Prints an error message.
 *
 * @param err Error Type.
 * @param func Function where the error append.
 */
void Error_print(Error err, char* func);

#endif