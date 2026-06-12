#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"
#include "ginput.h"
#include "cplworld.h"

#include <stdio.h>
#include <string.h>

extern float player_yFactor1;
extern CTICK player_yFactor2;
extern void optionsgui_init();

extern pos_t player_pos;

float saved_x = 0;
float saved_y = 0;
char has_save = 0;

char player_playing = 0;

void gamegui_key(char key[11]) {

	if (key[CKEY_JUMP] && caworld_onground() && player_yFactor2 < cplTicks()) {
		player_yFactor1 = 6.7;
	}

	if (key[CKEY_ATTACK]) {
		player_attack();
	}

	if (key[CKEY_ALT]) {
		player_attack();
	}

	if (key[CKEY_ESC]) {

		saved_x = player_pos.x;
		saved_y = player_pos.y;
		has_save = 1;

		optionsgui_init();
	}
}

void gamegui_draw() {
	cpl_drawWorld();
}

void gamegui_init() {

	caworld_load("TEST2");

	player_init();

	if (has_save) {
		player_pos.x = saved_x;
		player_pos.y = saved_y;
	}

	cplgui_setIdle(gamegui_draw);
	cplgui_setInput(gamegui_key);

	cpl_inputRepeat(0);

	player_playing = 1;
}