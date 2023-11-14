/**
 * @file Mana.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __MANA_H__
#define __MANA_H__

typedef struct {
    unsigned int level;
    unsigned int mana_real;
    unsigned int mana_max;
} ManaPool;

#define MANA_START 150

ManaPool Init_mana(void);
int Mana_max(int level);

#endif  // __MANA_H__