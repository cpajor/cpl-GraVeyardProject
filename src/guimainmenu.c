#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t snd;
csound_t title;
csoundcallback_t titl;

void mainmenu_key(char key[11]) {
	if (key[CKEY_DOWN] || key[CKEY_UP]) {
		csnd_playsound(snd);
		csnd_stopsound(titl);
	}
}

void mainmenu_draw() {
	cgui_background();
}

void mainmenu_init() {
	cplgui_setIdle(mainmenu_draw);
	cplgui_setInput(mainmenu_key);
	y1load(CSND_CLICK);
	snd = y1csound();
	y1load(CSND_TITLE);
	title = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(title, &titl);
}