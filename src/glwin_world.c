#include "cplvid.h"
#include "cplworld.h"
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>

extern size_t w_chunksSize;
extern char player_direction;

int w_camX = 0;
int w_camY = 0;

// tile size : 40x40
void cpl_drawTile(int type, int x, int y) {
	if (type >= 100 && type < 200) {
		tex_t tex = memgett("level1_0");
		if (type < 110) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type - 100), 0, 0.1, 0.25);
		}
		if (type >= 110 && type < 120) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type - 110), 0.25, 0.1, 0.25);
			if (type == 110)
				cpl_drawSpecial(CPLSPEC_FIRE, x - 20, y - 20);
		}
		if (type >= 120 && type < 130) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type - 120), 0.5, 0.1, 0.25);
		}
		if (type >= 130 && type < 140) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type - 130), 0.75, 0.1, 0.25);
		}
	}
}

void cpl_drawWorld() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int cw = (cpl_rWidth() / 2) * 0.5;
	int ch = (cpl_rHeight() / 2) * 0.5;
	
	glOrtho(w_camX - cw, w_camX + cw, w_camY - ch, w_camY + ch, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	//
	for (int i = 0; i < w_chunksSize; i++) {
		const edict_t* ed = ewgetEdict(i);
		if (!ed) continue;
		for (int j = 0; j < 64; j++) {
			edict_t e = ed[j];
			int x = i * 40;
			int y = j * 40;
			if (e.typeBack > 0) {
				glColor3f(0.7, 0.7, 0.7);
				glPushMatrix();
				glTranslatef(x, y, 0);
				glScalef(1, -1, 1);
				glTranslatef(-x, -y, 0);
				cpl_drawTile(e.typeBack, x, y);
				glPopMatrix();
			}
			if (e.type > 0) {
				glColor3f(1, 1, 1);
				glPushMatrix();
				glTranslatef(x, y, 0);
				glScalef(1, -1, 1);
				glTranslatef(-x, -y, 0);
				cpl_drawTile(e.type, x, y);
				glPopMatrix();
			}
			
		}
	}
	glPopMatrix();

	cpl_resetOrtho();

	glPushMatrix();
	glTranslatef((cpl_rWidth() / 2), (cpl_rHeight() / 2), 0);
	glScalef(2, 2, 1);
	if (player_direction) {
		glScalef(-1, 1, 1);
	}	
	glTranslatef(-(cpl_rWidth() / 2), -(cpl_rHeight() / 2), 0);

	cpl_drawClaw((cpl_rWidth() / 2), (cpl_rHeight() / 2));

	glPopMatrix();

}

void caworld_camera(pos_t pos) {
	w_camX = pos.x;
	w_camY = pos.y;
}