#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"
#include "ginput.h"
#include "cplworld.h"

#include <stdio.h>
#include <string.h>

extern float player_yFactor1;

char player_playing = 0;

void gamegui_key(char key[11]) {

	if (key[CKEY_JUMP] && caworld_onground()) {
		player_yFactor1 = 30;
	}
}

void gamegui_draw() {
	cpl_drawWorld();
}

void gamegui_init() {
	caworld_load("TEST2");
	player_init();
	cplgui_setIdle(gamegui_draw);
	cplgui_setInput(gamegui_key);
	cpl_inputRepeat(1);
	player_playing = 1;
}