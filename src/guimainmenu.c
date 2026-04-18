#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

tex_t back1;

void mainmenu_draw() {
	cpl_setColor(1, 1, 1, 1);
	cpl_rTexQuad(back1, 0, 0, 1024, 768);
}

void mainmenu_init() {
	back1 = memgett(TEX_MENU_0);
	cplgui_setIdle(mainmenu_draw);
}