#ifndef CPLWORLD_H
#define CPLWORLD_H
#include "cpl.h"

pos_t wpos(int x, int y);

char wposcmp(pos_t b1, pos_t b2);

edict_t* ewgetEdict(int pos);

#endif