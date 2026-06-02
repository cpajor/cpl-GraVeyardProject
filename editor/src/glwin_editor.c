#include "cplvid.h"
#include "editor.h"
#include <stdlib.h> 
#include <stdio.h>

extern char _cmd_show;
extern char* _cmd_buf;
extern char _choosed_gui;

extern int w_chunksSize;

extern edict_t* ewgetEdict(int pos);
extern void cpl_drawEditGuis(); 

// 0 - front / 1 - rear
char w_mode = 0;
int w_camX = -140;
int w_camY = 400;
int w_currX = 0;
int w_currY = 0;
pos_t w_curr;
pos_t w_cur2;

void cpl_drawTile(int type, int x, int y) {
	if (type == 1) {
		glColor4f(1, 1, 1, 0.25F);
		cpl_rColorQuad(x - 20, y - 20, 40, 40);
		return;
	}
	if (type == 2) {
		glColor4f(1, 1, 1, 0.25F);

		cpl_rColorQuad(x + 10, y - 20, 10, 40);

		return;
	}
	if (type >= 0x100 && type < 0x200) {
		glColor3f(1, 1, 1);
		tex_t tex = memgett("level1_0");
		if (type < 0x11A) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type & 0xF), 0, 0.1, 0.25);
			return;
		}
		if (type < 0x12A && type > 0x11F) {
			cpl_rTexQuadOff(tex, x - 20, y - 20, 40, 40, 0.1 * (type & 0xF), 0, 0.1, 0.25);
			return;
		}
	}


	cpl_setMode(CPLVID_DRAW_LINES);
	glColor3f(1, 0, 0);
	cpl_rColorQuad(x - 20, y - 20, 40, 40);
	cpl_setMode(CPLVID_DRAW_FILL);
}

void cpl_drawEdit() {
	char ca[60];

	glPushMatrix();
	glTranslatef(0, w_camY, 0);
	//
	for (int i = 0; i < 45; i++) {
		const edict_t* ed = ewgetEdict(i + (w_camX / 40));
		//if (i + (w_camX / 40) % 0xFF == 0) {}
		if (!ed) continue;
		for (int j = 0; j < 64; j++) {
			edict_t e = ed[j];
			int id = w_mode == 0 ? e.type : e.typeBack;
			if (id > 0) cpl_drawTile(id, (i * 40) - (w_camX % 40), -j * 40);
			if (i + (w_camX / 40) == w_currX && j == w_currY) {
				cpl_drawTile(1, (i * 40) - (w_camX % 40), -j * 40);
			}
		}
	}
	glPopMatrix();

	if (_choosed_gui == 0) {
		if (_cmd_show) {
			sprintf(ca, "%s\0", _cmd_buf);
			glColor3f(0, 0.75f, 0);
			cpl_drawConNoColorString("$", 0, 0);
			cpl_drawConString(ca, 24, 0);
		}
		else {
			sprintf(ca, "%i / %i\0", w_currX, w_currY);
			cpl_drawConString(ca, 0, 0);

			ZeroMemory(ca, 60);
			sprintf(ca, "%i / %i\0", w_camX, w_camY);
			cpl_drawConString(ca, 0, 20);

			ZeroMemory(ca, 60);
			sprintf(ca, "B-SIZE %i\0", memgeti("e_brushsize"));
			cpl_drawConString(ca, 0, 580);

			ZeroMemory(ca, 60);
			sprintf(ca, "B-TYPE %i\0", memgeti("e_brushtype"));
			cpl_drawConString(ca, 0, 560);

			if (w_mode) {
				cpl_drawConString("MODE: BACK", 0, 540);
			}
			else {
				cpl_drawConString("MODE: FRONT", 0, 540);
			}
		}
	} 
	else {

	}

}

void cpl_updateView() {
	w_currX = w_curr.x;
	w_currY = w_curr.y;
	if (w_currY < 0) w_curr.y = 0;
	if (w_currY > 63) w_curr.y = 63;
	if (w_currX < 0) w_curr.x = 0;
	if (w_currX > w_chunksSize - 1) w_curr.x = w_chunksSize - 1;

	int ydelta = (w_currY + 8) - (w_camY / 40);
	if (abs(ydelta) > 4) {
		w_camY += (ydelta > 0 ? 40 : -40);
	}
	int xdelta = (w_currX - 10) - (w_camX / 40);
	if (abs(xdelta) > 8) {
		w_camX += (xdelta > 0 ? 40 : -40);
	}



}