#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t snd;

void mainmenu_key(char key[11]) {
	if (key[CKEY_DOWN] || key[CKEY_UP]) {
		csnd_playsound(snd);
	}
}

void mainmenu_draw() {
	cgui_background();
}

void mainmenu_init() {
	cplgui_setIdle(mainmenu_draw);
	cplgui_setInput(mainmenu_key);
	y1load(SND_CLICK);
	snd = y1csound();
}