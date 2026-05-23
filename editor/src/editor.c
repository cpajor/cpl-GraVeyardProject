#include "cplvid.h"
#include "cplthread.h"
#include "cplrez.h"
#include "editor.h"

extern pos_t w_curr;

extern int c_state;

extern void _mem_init(); // mem.c
extern void _rnd_init(); // glwnd.c
extern void _rnd_thread(); // glwnd.c

extern void cplthr_init(); // cpl_thread.cpp
extern void _editorcmds_thread(int id); // editor_cmds.cpp

CTICK _game_uptime = 0;

CTICK cplTicks() {
	return _game_uptime;
}

void _editor_thread(int id) {
	DWORD nextTick = GetTickCount64();
	while (cplState()) {
		DWORD now = GetTickCount64();
		while (now >= nextTick) {
			//game_tick();

			_game_uptime++;
			nextTick += 100;
		}
	}
}

void postkeyboard(char key[64]) {
	if (key[CKEY_LEFT]) {
		w_curr.x--;

	}
	if (key[CKEY_RIGHT]) {
		w_curr.x++;

	}
	if (key[CKEY_UP]) {
		w_curr.y++;

	}
	if (key[CKEY_DOWN]) {
		w_curr.y--;

	}
	cpl_updateView();
}

char keys[64];

void keyboard_key(int key, char state) {
	keys[key] = !state;
	//
	postkeyboard(keys);
}

void keyboard_extended(unsigned int key, char state) {
	
}

void edit_loadRez() {
	memsett("blank", txGenBlank(1, 1));

	y1load(TEX_LEVEL1_0);
	memsett("level1_0", y1txCIG());

	y1zero();
}

void edit_start() {
	_mem_init();
	cplthr_init();
	_rnd_init();
	edit_loadRez();
	
	//
	cplthr_set(1, _editorcmds_thread);

	cplthr_set(0, _editor_thread);
	_rnd_thread();
}

int main(int argc, char** argv) {
	edit_start();
}