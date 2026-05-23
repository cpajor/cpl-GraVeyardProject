#include "cplvid.h"
#include <stdlib.h> 
#include <stdio.h>

int w_camX = 0;
int w_camY = 0;

void cpl_drawTile(int type, int x, int y) {
	if (type >= 0x100 && type < 0x200) {
		tex_t tex = memgett("level1_0");
		if (type < 0x110) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type & 0xF), 0, 0.1, 0.25);
		}
	}
}

void cpl_drawEdit() {
	char* ca = malloc(60);

	sprintf(ca, "%i : %i\0", w_camX, w_camY);

	glPushMatrix();
	glTranslatef(0, w_camY, 0);
	//
	for (int i = 0; i < 45; i++) {

		const edict_t* ed = wgetEdict(i + (w_camX / 40));
		if (!ed) continue;
		for (int j = 0; j < 64; j++) {
			edict_t e = ed[j];
			if (e.type > 0) cpl_drawTile(e.type, (i * 40) - (w_camX % 40), -j * 40);
		}
	}
	glPopMatrix();


	cpl_drawConString(ca, 0, 0);
}