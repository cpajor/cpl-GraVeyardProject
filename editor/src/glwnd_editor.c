#include "cplvid.h"
#include "editor.h"
#include <stdlib.h> 
#include <stdio.h>

int w_camX = -140;
int w_camY = 400;

int w_currX = 0;
int w_currY = 0;
pos_t w_curr;
pos_t w_cur2;

extern edict_t* ewgetEdict(int pos);

void cpl_drawTile(int type, int x, int y) {
	if (type == 1) {
		glColor4f(1, 1, 1, 0.25F);
		cpl_rColorQuad(x - 20, y - 20, 40, 40);
	}
	if (type == 2) {
		glColor4f(1, 1, 1, 0.25F);

		cpl_rColorQuad(x + 10, y - 20, 10, 40);
	}
	if (type >= 0x100 && type < 0x200) {
		glColor3f(1, 1, 1);
		tex_t tex = memgett("level1_0");
		if (type < 0x110) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type & 0xF), 0, 0.1, 0.25);
		}
	}
}

void cpl_drawEdit() {
	char ca[60];

	sprintf(ca, "%i / %i\0", w_currX, w_currY);

	glPushMatrix();
	glTranslatef(0, w_camY, 0);
	//
	for (int i = 0; i < 45; i++) {
		const edict_t* ed = ewgetEdict(i + (w_camX / 40));
		if (i + (w_camX / 40) % 0x255 == 0) {

		}
		if (!ed) continue;
		for (int j = 0; j < 64; j++) {
			edict_t e = ed[j];
			if (e.type > 0) cpl_drawTile(e.type, (i * 40) - (w_camX % 40), -j * 40);
			if (i + (w_camX / 40) == w_currX && j == w_currY) {
				cpl_drawTile(1, (i * 40) - (w_camX % 40), -j * 40);
			}
		}
	}
	glPopMatrix();

	cpl_drawConString(ca, 0, 0);

	ZeroMemory(ca, 60);
	sprintf(ca, "%i / %i\0", w_camX, w_camY);

	cpl_drawConString(ca, 0, 20);
}

void cpl_updateView() {
	w_currX = w_curr.x;
	w_currY = w_curr.y;
	if (w_currY < 0) w_curr.y = 0;
	if (w_currY > 63) w_curr.y = 63;
	if (w_currX < 0) w_curr.x = 0;

	int ydelta = (w_currY + 8) - (w_camY / 40);
	if (abs(ydelta) > 4) {
		w_camY += (ydelta > 0 ? 40 : -40);
	}
	int xdelta = (w_currX - 10) - (w_camX / 40);
	if (abs(xdelta) > 8) {
		w_camX += (xdelta > 0 ? 40 : -40);
	}



}