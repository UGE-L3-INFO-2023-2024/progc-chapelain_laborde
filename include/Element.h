/**
 * @file Element.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30-10-2023
 *
 */

#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <stdlib.h>
#include <time.h>

#define ROOTING_DURATION_MS 3000
#define SPRAYING_DURATION_MS 5000
#define HYDRO_DURATION_MS 10000
#define DENDRO_DURATION_MS 10000
#define DENDRO_NEXT_HIT_MS 500

/**************/
/* Structures */
/**************/

typedef enum {
    NONE,
    PYRO,
    DENDRO,
    HYDRO,
    SPRAYING,
    BURNING,
    ROOTING,
} Element_Type;

typedef struct {
    Element_Type main;                 // all
    Element_Type second;               // can only be spraying
    struct timespec end_apply_main;    // dendro, hydro, spraying
    struct timespec next_hit_main;     // dendro
    struct timespec end_apply_second;  // spraying
} Element;

/*************/
/* Functions */
/*************/

/**
 * @brief  Initialize a element.
 *
 * @return Element
 */
Element Elem_init(void);

#endif  // __ELEMENT_H__