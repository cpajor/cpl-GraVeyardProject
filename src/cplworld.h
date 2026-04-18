#ifndef CPLWORLD_H
#define CPLWORLD_H
#include "cpl.h"

location_t wlocation(double x, double y);

location_t wlocationb(pos_t b);

pos_t wblockpos(location_t l);

char wlocationcmp(pos_t b1, pos_t b2);

edict_t* wgetEdict(pos_t pos);

#endif