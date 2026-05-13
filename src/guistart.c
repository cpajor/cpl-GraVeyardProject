#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t snd;
csound_t title;
csoundcallback_t titl;

void startgui_key(char key[11]) {
	if (key[CKEY_DOWN] || key[CKEY_UP]) {
		csnd_playsound(snd);
		csnd_stopsound(titl);
	}
}

void startgui_draw() {
	//cgui_background();
	
}

void startgui_init() {
	cplgui_setIdle(startgui_draw);
	cplgui_setInput(startgui_key);
	y1load(CSND_CLICK);
	snd = y1csound();
	y1load(CSND_TITLE);
	title = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(title, &titl);
}