#ifndef CPLGUI_H
#define CPLGUI_H
#include "cpl.h"
#include "ginput.h"

void cplgui_setInit(cplgui_init_f in);
void cplgui_setIdle(cplgui_idle_f in);
void cplgui_setInput(cplgui_input_f in);

void cgui_background();
void cgui_popupBack(int width, int height);


#endif // !CPLGUI_H