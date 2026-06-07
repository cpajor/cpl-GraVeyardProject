#include "cplvid.h"
#include "cplthread.h"
#include "cplaudio.h"
#include "ginput.h"
#include "cplworld.h"

#include <stdlib.h>
#include <stdio.h>

extern void _rnd_init(); // glwnd.c
extern void _rnd_thread(); // glwnd.c
extern int c_state;

extern void cplgui_init(); // gui.c
extern void cplgui_input(char keys[11]); // gui.c
extern void cplgui_setInit(cplgui_init_f in); //gui.c

extern void rezLoadReg(); // rezman.c

extern void mainmenu_init(); // guimainmenu.c
extern void startgui_init(); // guistart.c

extern char player_playing;

CTICK _game_uptime = 0;
CTICK _game_worldTime = 0;

CTICK cplTicks() {
	return _game_uptime;
}

void _game_thread(int id) {
	CTICK nextTick = GetTickCount64();
	while (c_state) {
		CTICK now = GetTickCount64();
		while (now >= nextTick) {
			
			_game_uptime++;
			nextTick += 50;
		}
	}
}

void _game_invokeThread(int id) {
	CTICK nextTick = GetTickCount64();
	while (c_state) {
		CTICK now = GetTickCount64();
		while (now >= nextTick) {
			if (player_playing)
				caworld_tick();
			_game_worldTime++;
			nextTick += 10;
		}
	}
}

void StartGame() {
	_rnd_init();
	//cpl_fullscreen(1);
	rezLoadReg();

	//cplgui_setInit(startgui_init);
	cplgui_setInit(mainmenu_init);

	cplgui_init();
	cplthr_set(0, _game_thread);
	cplthr_set(1, _game_invokeThread);
	_rnd_thread();
}


char _ginput[11];
CTICK _grepeattick;
char _grepeat = 0;

// state = 1 -> down, state = 0 -> up
void keyboard_key(int key, char state) {
	_ginput[key] = !state;
	//

	if (!_grepeat) {
		if (!state) {
			if (_grepeattick >= cplTicks()) return;
			_grepeattick = cplTicks();
		}
		else return;
	}
	cplgui_input(_ginput);
}

void cpl_inputRepeat(char repeating) {
	_grepeat = repeating;
}

char cpl_ginput(char ckey) {
	if (ckey >= 0 && ckey < 11) {
		return _ginput[ckey];
	}
}