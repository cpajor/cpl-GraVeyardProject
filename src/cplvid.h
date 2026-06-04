#ifndef VID_H
#define VID_H
#include "cpl.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define CPLVID_DRAW_FILL GL_FILL
#define CPLVID_DRAW_LINES GL_LINE

void txBegin(tex_t tex);
void txEnd();

tex_t y1txCIG();
tex_t txGenBlank(int width, int height);

void cpl_setMode(int mode);
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

void cpl_resetOrtho();
int cpl_rWidth();
int cpl_rHeight();

void cpl_fullscreen(char fullscr);

// world

void cpl_drawWorld();

// etc

#define CPLSPEC_COIN 10

void cpl_drawSpecial(char type, int x, int y);

void cpl_drawClaw(int x, int y, unsigned short type);

#endif // !VID_H
