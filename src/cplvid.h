#ifndef VID_H
#define VID_H
#include "cpl.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

void txBegin(tex_t tex);
void txEnd();

tex_t y1txCIG();

void cpl_setColor(float r, float g, float b, float a);
void cpl_rColorQuad(int x, int y, int width, int height);
void cpl_rTexQuad(tex_t tex, int x, int y, int width, int height);
void cpl_rTexQuadOff(tex_t tex, int x, int y, int width, int height, float ofx, float ofy, float ofstepx, float ofstepy);

void cpl_drawConString(char* c, int x, int y);
void cpl_drawConStringN(char* c, int x, int y, int N);
void cpl_drawConNoColorString(char* c, int x, int y);
void cpl_drawConNoColorStringN(char* c, int x, int y, int N);
void cpl_drawConChar(char c, int x, int y);
void cpl_drawConNoColorChar(char c, int x, int y);

int cpl_rWidth();
int cpl_rHeight();

#endif // !VID_H
