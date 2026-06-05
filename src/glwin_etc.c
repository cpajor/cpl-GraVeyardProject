#include "cplvid.h"
#include "cplworld.h"
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>

void cpl_drawSpecial(char type, int x, int y) {
	if (type == CPLSPEC_COIN) {
		cpl_rTexQuadOff(memgett("spec_coin"), x, y, 32, 32, 1, ((cplTicks() / 2) % 9) * 0.1, 1, 0.1);
	}
	if (type == CPLSPEC_FIRE) {
		char a = (cplTicks() % 12) / 3;
		a += (x * y) % 3;
		cpl_rTexQuadOff(memgett("spec_fire"), x, y, 40, 40, 0, a * 0.25, 1, 0.25);
	}
}

tex_t cclaw_tex[16];
/*
	name    : frame
	idle    : 1 - 8
	run     : 10 - 20
	attack1 : 21 - 39
	fall    : 30 - 39
	jump    : 40 - 49
	attackj ; 50 - 59
*/
void cpl_drawClaw(int x, int y) {
	int type = player_animState();
	if (type > 20 && type < 29) {
		cpl_rTexQuadOff(cclaw_tex[2], x - 30, y - 60, 120, 80, 0, (type - 21) * 0.25, 1, 0.25);
	}
	if (type < 9 && type > 0) {
		glColor3f(1, 1, 1);
		cpl_rColorQuad(x - 30, y - 60, 60, 80);
		cpl_rTexQuadOff(cclaw_tex[0], x - 30, y - 60, 60, 80, 0, (type - 1) * 0.125, 1, 0.125);
	}
	if (type > 9 && type < 21) {
		cpl_rTexQuadOff(cclaw_tex[1], x - 40, y - 60, 80, 80, 0, (type - 10) * 0.1, 1, 0.1);
	}
	if (type > 30 && type < 40) {
		cpl_rTexQuadOff(cclaw_tex[3], x - 30, y - 60, 60, 80, 0, (type - 30) * 0.25, 1, 0.25);
	}
	if (type > 39 && type < 50) {
		cpl_rTexQuadOff(cclaw_tex[4], x - 30, y - 60, 80, 80, 0, (type - 40) * 0.125, 1, 0.125);
	}
	if (type > 49 && type < 60) {
		cpl_rTexQuadOff(cclaw_tex[5], x - 30, y - 60, 120, 80, 0, (type - 50) * 0.25, 1, 0.25);
	}
}