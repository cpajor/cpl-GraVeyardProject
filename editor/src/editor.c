#include "cplvid.h"
#include "cplthread.h"
#include "cplrez.h"
#include "editor.h"
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern pos_t w_curr;
extern int c_state;

extern void _mem_init(); // mem.c
extern void _rnd_init(); // glwin_cpl.c
extern void _rnd_thread(); // glwin_cpl.c
extern void cmd_callCmd(char* str); // editor_cmds.c

extern void cplthr_init(); // cpl_thread.cpp

char _cmd_show = 0;
char* _cmd_buf;
char* _editor_console;

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

void postkeyboard(char key[11]) {

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

char keys[11];

void keyboard_key(int key, char state) {
	if (_cmd_show) return;

	keys[key] = !state;
	//
	postkeyboard(keys);
}

void keyboard_extended(unsigned int key, char state) {
	
	if (state) return;
	if (key == VK_OEM_3) { // `
		_cmd_show = !_cmd_show;
		return;
	}
	if (key == VK_RETURN) {
		cmd_callCmd(_cmd_buf);

		_cmd_buf[0] = '\0';
		return;
	}
	if (key == VK_BACK) {
		int c = strlen(_cmd_buf);

		if (c) _cmd_buf[c - 1] = '\0';
		
		return;
	}
	if (_cmd_show) {
		if (strlen(_cmd_buf) < 255) {
			sprintf(_cmd_buf, "%s%c", _cmd_buf, key);
		} 
	}
	if (key == 'S' && keys[CKEY_ATTACK]) { // S
		cworld_save();
	}
	if (key == 'T' && keys[CKEY_ATTACK]) { // T
		cworld_load();
	}
	if (key == VK_TAB) {

	}
}

void edit_loadRez() {
	memsett("blank", txGenBlank(1, 1));

	y1load(TEX_LEVEL1_0);
	memsett("level1_0", y1txCIG());

	y1zero();
}

void edit_start() {
	_mem_init();
	_cmd_buf = malloc(sizeof(char) * 256);
	_cmd_buf[0] = '\0';
	cplthr_init();
	_rnd_init();
	edit_loadRez();
	
	//

	cplthr_set(0, _editor_thread);
	_rnd_thread();
}

int main(int argc, char** argv) {
	edit_start();
}