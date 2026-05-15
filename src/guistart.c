#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

#include <stdio.h>
#include <string.h>

csound_t title;
csoundcallback_t titl;

long startgui_uptime = -1;
int __frame = 0;
tex_t _intro0;
tex_t _intro[6];

extern void mainmenu_init(); // guimainmenu.c

void startgui_key(char key[11]) {
	if (key[CKEY_JUMP]) {
		if (__frame < 99) {
			__frame = 99;
		}
	}
}

void startgui_draw() {
	if (startgui_uptime < 0) {
		startgui_uptime = cplTicks();
	}
	if (startgui_uptime < cplTicks() && __frame < 100) {
		startgui_uptime = cplTicks();
		__frame++;
	}
	cpl_rTexQuad(_intro0, 0, 0, cpl_rWidth(), cpl_rHeight());

	if (__frame < 61) {
		tex_t cur = _intro[(__frame / 10)];
		cpl_rTexQuadOff(cur, 0, 0, cpl_rWidth(), cpl_rHeight(), 0, 0.1 * (__frame % 10), 1, 0.1);
	}

	/*
	glClear(GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // color off

	// mask drawing, only glvertex


	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	glStencilMask(0x00);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	
	//

	glDisable(GL_STENCIL_TEST);
	*/


	
	if (__frame > 99) {
		csnd_stopsound(titl);
		cplgui_setInit(mainmenu_init);
		cplgui_init();
	}
}

void startgui_init() {
	cplgui_setIdle(startgui_draw);
	cplgui_setInput(startgui_key);
	y1load(CSND_TITLE);
	title = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(title, &titl);
	y1load(TEX_MENU_1);
	_intro0 = y1txCIG();
	for (int i = 1; i < 7; i++) {
		char* buf = malloc(sizeof(char) * 20); 
		sprintf(buf, "movies/intro%i.cig", i);
		y1load(buf);
		_intro[i - 1] = y1txCIG();
	}
}