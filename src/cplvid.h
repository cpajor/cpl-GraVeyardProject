#ifndef VID_H
#define VID_H
#include "cpl.h"

void txBegin(tex_t tex);

void txEnd();

tex_t y1txCIG();

void cpl_setColor(float r, float g, float b, float a);

void cpl_rTexQuad(tex_t tex, int x, int y, int width, int height);

void cpl_rTexQuadOff(tex_t tex, int x, int y, int width, int height, float ofx, float ofy, float ofstepx, float ofstepy);

#endif // !VID_H
