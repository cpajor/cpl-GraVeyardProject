#include "cplgui.h"
#include "cplvid.h"
#include "cplrez.h"

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

char cg_activepopup = 0;

tex_t cg_back1 = 0;

void cgui_background() {
	if (cg_back1 == 0) cg_back1 = memgett(TEX_MENU_0);
	if (cg_activepopup) {
		cpl_setColor(0.67, 0.67, 0.67, 1);
	}
	else {
		cpl_setColor(1, 1, 1, 1);
	}
	cpl_rTexQuad(cg_back1, 0, 0, cpl_rWidth(), cpl_rHeight());
}

void cgui_popupBack(int width, int height) {
	cg_activepopup = 1;
}