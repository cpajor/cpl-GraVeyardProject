#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

CPLMEM cclick1;

void mainmenu_key(char key[11]) {
	if (key[CKEY_DOWN] || key[CKEY_UP]) {
		csnd_playsound(cclick1);
		
	}
}

void mainmenu_draw() {
	cgui_background();
}

void mainmenu_init() {
	cplgui_setIdle(mainmenu_draw);
	cplgui_setInput(mainmenu_key);
	cclick1 = memgets(SND_CLICK);
}