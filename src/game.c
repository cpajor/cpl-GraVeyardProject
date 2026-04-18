#include "cpl.h"
#include "cplthread.h"
#include "cplaudio.h"
#include "ginput.h"
#include <stdlib.h>
#include <stdio.h>

extern void _rnd_init(); // glwnd.c
extern void _rnd_thread(); // glwnd.c

extern void _csnd_thr(); // soundengine.c

extern void cplgui_init(); // gui.c
extern void cplgui_input(char keys[11]); // gui.c

extern void rezLoadReg(); // rezman.c

extern void mainmenu_init(); // guimainmenu.c

void StartGame() {
	_rnd_init();
	rezLoadReg();
	cplthr_set(1, _csnd_thr);

	mainmenu_init();

	cplgui_init();
	_rnd_thread();
}


char _ginput[11];

// state = 0 -> down, state = 1 -> up
void keyboard_key(int key, char state) {
	_ginput[key] = state;
	//
	if (_ginput[CKEY_ENTER]) {

	}
	if (_ginput[CKEY_UP]) {

	}
	if (_ginput[CKEY_DOWN]) {

	}

	cplgui_input(_ginput);
}