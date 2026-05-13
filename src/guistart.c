#include "cplgui.h"
#include "cplvid.h"
#include "cplaudio.h"
#include "cplrez.h"

csound_t title;
csoundcallback_t titl;

extern void mainmenu_init(); // guimainmenu.c

void startgui_key(char key[11]) {
	if (key[CKEY_JUMP]) {
		csnd_stopsound(titl);
		cplgui_setInit(mainmenu_init);
		cplgui_init();
	}
}

void startgui_draw() {
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

}

void startgui_init() {
	cplgui_setIdle(startgui_draw);
	cplgui_setInput(startgui_key);
	y1load(CSND_TITLE);
	title = y1csoundt(CSOUND_MUSIC);
	csnd_playsoundc(title, &titl);
}