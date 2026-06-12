
#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"



char mainsel1 = 0;
char showCredits1 = 0;

extern void gamegui_init(); // guigame.c

void optionsgui_key(char key[11]) {
	if (showCredits1) {
		showCredits1 = 0;
		return;
	}
	if (key[CKEY_DOWN]) {
		
		mainsel1++;
		if (mainsel1 > 3) mainsel1 = 0;
	}
	if (key[CKEY_UP]) {
		
		mainsel1--;
		if (mainsel1 < 0) mainsel1 = 3;
	}
	if (key[CKEY_ENTER] && !showCredits1) {
		if (mainsel1 == 0) {
		
		gamegui_init();
		
		}
		if (mainsel1 == 2) {
			showCredits1 = 1;
		}
		if (mainsel1 == 3) {
			exit(0);
		}
	}
}

void optionsgui_draw() {
	cgui_background();
	int hig = cpl_rHeight() / 4;
	if (showCredits1) {
		glPushMatrix();
		glScalef(2, 2, 1);

		cpl_drawSpecial(CPLSPEC_COIN, 8, 8);
		cpl_drawConString("CREDITS", 56, 16);

		glPopMatrix();

		cpl_drawConString("GAME CREATED ONLY FOR EDUCATIONAL PURPOSES", 48, 128);
		cpl_drawConString("MOST RESOURCES FROM CAPTAIN CLAW", 48, 128 + 64);
		cpl_drawConString("BY MONOLITH STUDIO (1997)", 48, 128 + 96);

		cpl_drawConString("CODING & PRODUCTION: CPAJOR", 48, 128 + 160);
		cpl_drawConString("MENTAL SUPPORT: UBER67MATI", 48, 128 + 192);
		cpl_drawConString("GRAPHICS EDIT: CPAJOR", 48, 128 + 224);

	}
	else {
		

	  glPushMatrix();
    glScalef(2, 2, 1);

    cpl_drawConString("PLAY", 56, hig);
    cpl_drawConString("OPTIONS", 56, hig + 32);
    cpl_drawConString("CREDITS", 56, hig + 64);
    cpl_drawConString("QUIT", 56, hig + 96);

    cpl_drawSpecial(CPLSPEC_COIN, 8, hig + (32 * mainsel1) - 8);

    glPopMatrix();
	}
}

void optionsgui_init() {
	cplgui_setIdle(optionsgui_draw);
	cplgui_setInput(optionsgui_key);
	
}