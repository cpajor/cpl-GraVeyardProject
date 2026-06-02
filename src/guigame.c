#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"
#include "ginput.h"

#include <stdio.h>
#include <string.h>

extern int w_camX;
extern int w_camY;

void gamegui_key(char key[11]) {
	if (key[CKEY_LEFT]) {
		w_camX -= 10;
	}
	if (key[CKEY_RIGHT]) {
		w_camX += 10;
	}

	if (key[CKEY_UP]) {
		w_camY += 10;
	}
	if (key[CKEY_DOWN]) {
		w_camY -= 10;
	}
}

void gamegui_draw() {
	cpl_drawWorld();
}

void gamegui_init() {
	cplgui_setIdle(gamegui_draw);
	cplgui_setInput(gamegui_key);
	cpl_inputRepeat(1);
}