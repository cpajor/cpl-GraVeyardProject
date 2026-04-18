#include "cplgui.h"
#include "cplvid.h"

cplgui_init_f cgui_init;
cplgui_idle_f cgui_idle;
cplgui_input_f cgui_input;

void cplgui_setInit(cplgui_init_f in) {
	cgui_init = in;
}

void cplgui_setIdle(cplgui_idle_f in) {
	cgui_idle = in;
}

void cplgui_setInput(cplgui_input_f in) {
	cgui_input = in;
}

void cplgui_init() {
	if (cgui_init != 0) cgui_init();
}

void cplgui_idle() {
	if (cgui_idle != 0) cgui_idle();
}

void cplgui_input(char keys[11]) {
	if (cgui_input != 0) cgui_input(keys);
}