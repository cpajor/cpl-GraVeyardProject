#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t selectsnd;
csound_t titlesnd;
csoundcallback_t titlcall;

char mainsel = 0;
char showCredits = 0;

void mainmenu_key(char key[11]) {
	if (showCredits) {
		showCredits = 0;
		return;
	}
	if (key[CKEY_DOWN]) {
		csnd_playsound(selectsnd);
		mainsel++;
		if (mainsel > 3) mainsel = 0;
	}
	if (key[CKEY_UP]) {
		csnd_playsound(selectsnd);
		mainsel--;
		if (mainsel < 0) mainsel = 3;
	}
	if (key[CKEY_ENTER] && !showCredits) {
		if (mainsel == 0) {
			csnd_stopsound(titlcall);
			// TODO game
		}
		if (mainsel == 2) {
			showCredits = 1;
		}
		if (mainsel == 3) {
			exit(0);
		}
	}
}

void mainmenu_draw() {
	cgui_background();
	int hig = cpl_rHeight() / 3;
	if (showCredits) {
		glPushMatrix();
		glScalef(2, 2, 1);

		cpl_drawSpecial(CPLSPEC_COIN, 8, 8);
		cpl_drawConString("CREDITS", 56, 16);

		glPopMatrix();

		cpl_drawConString("GAME CREATED FOR EDUCATIONAL PURPOSES", 48, 128);
		cpl_drawConString("RESOURCES FROM CAPTAIN CLAW", 48, 128 + 64);
		cpl_drawConString("BY MONOLITH STUDIO (1997)", 48, 128 + 96);

		cpl_drawConString("CODING & PRODUCTION: CPAJOR", 48, 128 + 160);
		cpl_drawConString("MENTAL SUPPORT: UBER67MATI", 48, 128 + 192);
		cpl_drawConString("GRAPHICAL EDIT: CPAJOR", 48, 128 + 224);

	}
	else {
		glPushMatrix();
		glScalef(2, 2, 1);
	
		cpl_drawConString("PLAY", 56, hig);
		cpl_drawConString("OPTIONS", 56, hig + 32);
		cpl_drawConString("CREDITS", 56, hig + 64);
		cpl_drawConString("QUIT", 56, hig + 96);
		cpl_drawSpecial(CPLSPEC_COIN, 8, hig + (32 * mainsel) - 8);
	
		glPopMatrix();
	}
}

void mainmenu_init() {
	cplgui_setIdle(mainmenu_draw);
	cplgui_setInput(mainmenu_key);
	y1load(CSND_SEL);
	selectsnd = y1csound();
	y1load(CSND_MENU);
	titlesnd = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(titlesnd, &titlcall);
}