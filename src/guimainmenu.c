#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t snd;
csound_t title;
csoundcallback_t titl;

char mainsel = 0;

void mainmenu_key(char key[11]) {
	if (key[CKEY_DOWN]) {
		csnd_playsound(snd);
		mainsel++;
		if (mainsel > 3) mainsel = 0;
	}
	if (key[CKEY_UP]) {
		csnd_playsound(snd);
		mainsel--;
		if (mainsel < 0) mainsel = 3;
	}
	if (key[CKEY_ENTER]) {
		if (mainsel == 1) {
			csnd_stopsound(titl);
			// TODO game
		}
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
	y1load(CSND_MENU);
	title = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(title, &titl);
}