#include "cplvid.h"
#include "cplworld.h"
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>

void cpl_drawSpecial(char type, int x, int y) {
	if (type == CPLSPEC_COIN) {
		cpl_rTexQuadOff(memgett("spec_coin"), x, y, 32, 32, 1, ((cplTicks() / 2) % 9) * 0.1, 1, 0.1);
	}

}

tex_t cclaw_tex[8];
/*
	name    : frame
	idle    : 1 - 8
	run     : 10 - 20
	attack1 : 21 - 24
	attack2 : 25 - 29
*/
void cpl_drawClaw(int x, int y) {
	int type = player_animState();
	if (type > 20 && type < 25) {
		cpl_rTexQuadOff(cclaw_tex[2], x - 60, y - 60, 120, 80, 0, (type - 20) * 0.25, 1, 0.25);
	}
	if (type < 9 && type > 0) {
		cpl_rTexQuadOff(cclaw_tex[0], x - 30, y - 60, 60, 80, 1, (type - 1) * 0.125, 1, 0.125);
	}
	if (type > 9 && type < 21) {
		cpl_rTexQuadOff(cclaw_tex[1], x - 40, y - 60, 80, 80, 1, (type - 10) * 0.1, 1, 0.1);
	}
}